// Задание 2. Консольное меню для проверки класса Money.

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include "task2/money.h"

#ifdef _WIN32
#include <windows.h>
#endif  // _WIN32

namespace {

    using ::lab1::Money;

    constexpr int64_t kMaxRubles = 4294967295;
    constexpr int64_t kMaxKopeks = 99;
    constexpr int64_t kMaxShortKopeks = 32767;
    constexpr std::string::size_type kMaxDigits = 18;

    std::string Trim(const std::string& text) {
        const std::string kSpaces = " \t\r\n";
        std::string::size_type first = text.find_first_not_of(kSpaces);
        if (first == std::string::npos) {
            return "";
        }
        std::string::size_type last = text.find_last_not_of(kSpaces);
        return text.substr(first, last - first + 1);
    }

    bool ParseNumber(const std::string& text, int64_t max_value,
                     int64_t* result) {
        if (text.empty() || text.size() > kMaxDigits) {
            return false;
        }
        int64_t value = 0;
        std::string::size_type i = 0;
        for (i = 0; i < text.size(); ++i) {
            if (text[i] < '0' || text[i] > '9') {
                return false;
            }
            value = value * 10 + (text[i] - '0');
        }
        if (value > max_value) {
            return false;
        }
        *result = value;
        return true;
    }

    int64_t ReadNumber(const std::string& prompt, int64_t max_value) {
        std::string line;
        int64_t value = 0;
        bool is_correct = false;
        while (!is_correct) {
            std::cout << prompt;
            if (!std::getline(std::cin, line)) {
                std::cout << "\nВвод прерван.\n";
                std::exit(EXIT_FAILURE);
            }
            is_correct = ParseNumber(Trim(line), max_value, &value);
            if (!is_correct) {
                std::cout << "Ошибка: нужно целое число от 0 до " << max_value
                          << ". Повторите ввод.\n";
            }
        }
        return value;
    }

// Reads rubles as unsigned int.
    unsigned int ReadRubles(const std::string& prompt) {
        return static_cast<unsigned int>(ReadNumber(prompt, kMaxRubles));
    }

    short int ReadKopeks(const std::string& prompt) {
        return static_cast<short int>(ReadNumber(prompt, kMaxKopeks));
    }

    Money ReadMoney(const std::string& name) {
        std::cout << "Введите сумму " << name << ":\n";
        unsigned int rubles = ReadRubles("  рубли: ");
        short int kopeks = ReadKopeks("  копейки (0-99): ");
        return Money(rubles, kopeks);
    }

    void TestConstructors() {
        std::cout << "\nТест конструкторов\n";
        Money by_default;
        std::cout << "1) Money():                " << by_default << "\n";

        std::cout << "2) Money(рубли, копейки). Копейки > 99 переходят в рубли.\n";
        unsigned int rubles = ReadRubles("  рубли: ");
        short int kopeks = static_cast<short int>(
                ReadNumber("  копейки (0-32767): ", kMaxShortKopeks));
        Money two_args(rubles, kopeks);
        std::cout << "   результат: " << two_args << "\n";

        std::cout << "3) Money(рубли).\n";
        unsigned int only_rubles = ReadRubles("  рубли: ");
        Money from_rubles(only_rubles);
        std::cout << "   результат: " << from_rubles << "\n";

        Money copy(two_args);
        std::cout << "4) Копия пункта 2:         " << copy << "\n";
    }

    void TestProperties() {
        std::cout << "\nТест свойств\n";
        Money money(5, 30);
        std::cout << "Начальное значение: " << money << "\n";
        unsigned int rubles = ReadRubles("Новые рубли: ");
        short int kopeks = static_cast<short int>(
                ReadNumber("Новые копейки (0-32767): ", kMaxShortKopeks));
        money.set_rubles(rubles);
        bool is_set = money.set_kopeks(kopeks);
        if (!is_set) {
            std::cout << "Копейки отклонены: допустимы значения от 0 до 99.\n";
        }
        std::cout << "rubles() = " << money.rubles()
                  << ", kopeks() = " << money.kopeks() << "\n";
        std::cout << "Итог: " << money << "\n";
    }

    void TestSubtract() {
        std::cout << "\nВычитание Money: метод Subtract\n";
        Money first = ReadMoney("A (уменьшаемое)");
        Money second = ReadMoney("B (вычитаемое)");
        std::cout << "A = " << first << "\nB = " << second << "\n";
        std::cout << "A.Subtract(B) = " << first.Subtract(second) << "\n";
        std::cout << "B.Subtract(A) = " << second.Subtract(first)
                  << "  (меньше нуля быть не может)\n";
    }

    void TestIncrementDecrement() {
        std::cout << "\nОперации ++ и --\n";
        Money money = ReadMoney("M");
        std::cout << "M    = " << money << "\n";
        std::cout << "++M  = " << ++money << "\n";
        std::cout << "M++  = " << money++ << "  (после: " << money << ")\n";
        std::cout << "--M  = " << --money << "\n";
        std::cout << "M--  = " << money-- << "  (после: " << money << ")\n";
    }

    void TestConversions() {
        std::cout << "\nПриведение типов\n";
        Money money = ReadMoney("M");
        unsigned int whole_rubles = money;
        double fraction = static_cast<double>(money);
        std::cout << "M = " << money << "\n";
        std::cout << "unsigned int (неявно): " << whole_rubles << "\n";
        std::cout << "double (явно):         " << fraction << "\n";
    }

    void TestMinus() {
        std::cout << "\nБинарный минус\n";
        Money first = ReadMoney("A");
        Money second = ReadMoney("B");
        unsigned int rubles = ReadRubles("Целое число рублей N: ");
        std::cout << "A - B = " << first - second << "\n";
        std::cout << "B - A = " << second - first << "\n";
        std::cout << "A - N = " << first - rubles << "\n";
        std::cout << "(если вычитаемое больше, результат равен 0)\n";
    }

}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif  // _WIN32
    bool is_running = true;
    int64_t choice = 0;
    while (is_running) {
        std::cout << "\nЗадание 2: класс Money\n"
                     "1. Конструкторы\n"
                     "2. Свойства\n"
                     "3. Метод Subtract\n"
                     "4. Операции ++ и --\n"
                     "5. Приведение типов\n"
                     "6. Бинарный минус (Money и unsigned int)\n"
                     "0. Выход\n";
        choice = ReadNumber("Ваш выбор: ", 6);
        switch (choice) {
            case 1: {
                TestConstructors();
                break;
            }
            case 2: {
                TestProperties();
                break;
            }
            case 3: {
                TestSubtract();
                break;
            }
            case 4: {
                TestIncrementDecrement();
                break;
            }
            case 5: {
                TestConversions();
                break;
            }
            case 6: {
                TestMinus();
                break;
            }
            default: {
                is_running = false;
                break;
            }
        }
    }
    std::cout << "Программа завершена.\n";
    return EXIT_SUCCESS;
}
