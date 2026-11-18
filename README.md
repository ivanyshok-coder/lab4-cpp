# Кудряшов Иван, ИТ-5, Лабораторная №4

```
.
├── task1/            # Задание 1
│   ├── money.h
│   ├── money.cc
│   └── main.cc
├── task2/            # Задание 2
│   ├── money.h
│   ├── money.cc
│   └── main.cc
├── screenshots/      # скриншоты для отчёта
└── README.md
```

# Задание 1

## Задача 1

### Текст задачи

Реализовать определение класса (поля, свойства, конструкторы (не менее трёх), перегрузку оператора вывода для вывода полей, заданный метод согласно варианту). Протестировать все методы, включая конструкторы, все исходные данные вводятся с клавиатуры, не забывайте проверять данные на корректность.

**Вариант 8.** Название класса — `Money`. Поля — `unsigned int rubles`, `short int kopeks`. Метод — вычитание переменной типа `Money` (учесть, что денежная величина не может быть меньше 0). Результат должен быть типа `Money`.

### Алгоритм решения

Код: [`task1/money.h`](task1/money.h), [`task1/money.cc`](task1/money.cc), [`task1/main.cc`](task1/main.cc).

**Поля:** `unsigned int rubles\_`, `short int kopeks\_`. Инвариант: `0 <= kopeks\_ <= 99`.

**Конструкторы:**

1. `Money()` — нулевая сумма.
2. `Money(unsigned int rubles, short int kopeks)` — копейки больше 99 переводятся в рубли (`12 руб. 250 коп.` → `14 руб. 50 коп.`).
3. `explicit Money(unsigned int rubles)` — только рубли.
4. Конструктор копирования (`= default`).

**Свойства:** `rubles()`, `kopeks()`, `set\_rubles()`, `set\_kopeks()`. Сеттер копеек возвращает `false` и не меняет значение, если оно вне диапазона 0–99.

**Оператор вывода** `operator<<` печатает сумму как `12 руб. 05 коп.`.

**Метод вычитания** `Money Subtract(const Money\& other) const`:

1. Перевести обе суммы в копейки: `рубли \* 100 + копейки` (тип `int64\_t`, чтобы не было переполнения).
2. Если вычитаемое больше или равно уменьшаемому — вернуть `0 руб. 00 коп.`.
3. Иначе вычесть копейки и перевести результат обратно: рубли = `разность / 100`, копейки = `разность % 100`.

**Проверка ввода.** Функция `ReadNumber` читает строку целиком и повторяет запрос, пока не будет введено целое неотрицательное число в допустимом диапазоне. Отклоняются пустая строка, буквы, знак минус, дробные числа, слишком большие значения. Копейки при вводе суммы допускаются только от 0 до 99.

### Тестирование

|Пункт меню|Ввод|Ожидаемый результат|
|-|-|-|
|Меню|`abc`, `-5`|сообщение об ошибке, повторный запрос|
|1. Конструкторы|`12`, `250`, `7`|`14 руб. 50 коп.`; `7 руб. 00 коп.`; копия `14 руб. 50 коп.`|
|2. Свойства|`100`, `150`|рубли = 100, копейки отклонены (остались 30)|
|3. Вычитание|A = `10 50`, B = `3 75`|`A - B = 6 руб. 75 коп.`, `B - A = 0 руб. 00 коп.`|

Скриншоты:

!\[Конструкторы](screenshots/task1\_constructors.png)

!\[Свойства](screenshots/task1\_properties.png)

!\[Вычитание](screenshots/task1\_subtract.png)

<details>
<summary>Текстовый вывод программы</summary>

```

Задание 1: класс Money
1. Конструкторы
2. Свойства
3. Вычитание Money (Subtract)
0. Выход
Ваш выбор: Ошибка: нужно целое число от 0 до 3. Повторите ввод.
Ваш выбор: Ошибка: нужно целое число от 0 до 3. Повторите ввод.
Ваш выбор: 
Тест конструкторов
1) Money():                0 руб. 00 коп.
2) Money(рубли, копейки). Копейки > 99 переходят в рубли.
  рубли:   копейки (0-32767):    результат: 14 руб. 50 коп.
3) Money(рубли).
  рубли:    результат: 7 руб. 00 коп.
4) Копия пункта 2:         14 руб. 50 коп.

Задание 1: класс Money
1. Конструкторы
2. Свойства
3. Вычитание Money (Subtract)
0. Выход
Ваш выбор: 
Тест свойств
Начальное значение: 5 руб. 30 коп.
Новые рубли: Новые копейки (0-32767): Копейки отклонены: допустимы значения от 0 до 99.
rubles() = 100, kopeks() = 30
Итог: 100 руб. 30 коп.

Задание 1: класс Money
1. Конструкторы
2. Свойства
3. Вычитание Money (Subtract)
0. Выход
Ваш выбор: 
Вычитание Money: метод Subtract
Введите сумму A (уменьшаемое):
  рубли:   копейки (0-99): Введите сумму B (вычитаемое):
  рубли:   копейки (0-99): A = 10 руб. 50 коп.
B = 3 руб. 75 коп.
A.Subtract(B) = 6 руб. 75 коп.
B.Subtract(A) = 0 руб. 00 коп.  (меньше нуля быть не может)

Задание 1: класс Money
1. Конструкторы
2. Свойства
3. Вычитание Money (Subtract)
0. Выход
Ваш выбор: Программа завершена.
```

</details>

# Задание 2

## Задача 1

### Текст задачи

Добавить к реализованному в первом задании классу указанные в варианте перегруженные операции. В главной функции `main` показать работу всех функций с дружественным интерфейсом.

**Вариант 8.** Класс `Money`. Унарные операции: `++` — добавление копейки к объекту типа `Money`; `--` — вычитание копейки из объекта типа `Money`. Операции приведения типа: `unsigned int` (неявная) — результатом является количество рублей (копейки отбрасываются); `double` (явная) — результатом являются копейки, переведённые в рубли, целые рубли отбрасываются, результат < 1. Бинарные операции: `-` беззнаковое целое число, результат должен быть типа `Money`; `-` `Money m`, результат должен быть типа `Money`. Результат не может быть отрицательным.

### Алгоритм решения

Код: [`task2/money.h`](task2/money.h), [`task2/money.cc`](task2/money.cc), [`task2/main.cc`](task2/main.cc). Класс из задания 1 дополнен операциями:

|Операция|Алгоритм|
|-|-|
|`++` (префиксная и постфиксная)|если `kopeks\_ < 99` — увеличить копейки; иначе рубли + 1, копейки = 0 (при переполнении рублей сумма не меняется)|
|`--` (префиксная и постфиксная)|если `kopeks\_ > 0` — уменьшить копейки; иначе, если рубли > 0, то рубли − 1, копейки = 99; нулевая сумма остаётся нулевой|
|`operator unsigned int()` (неявная)|вернуть `rubles\_`|
|`explicit operator double()`|вернуть `kopeks\_ / 100.0`|
|`operator-(const Money\&, unsigned int)`|вычесть `N` рублей как `Subtract(Money(N))`, результат не меньше нуля|
|`operator-(const Money\&, const Money\&)`|вызвать `Subtract`, результат не меньше нуля|

Бинарные операторы вынесены из класса в пространство имён (по Google Style: неизменяющие бинарные операторы — свободные функции), постфиксные формы возвращают старое значение. В `main` реализовано меню, которое показывает работу всех конструкторов, свойств, `Subtract`, `++`, `--`, обоих приведений и обоих вариантов бинарного минуса. Ввод проверяется так же, как в задании 1.

### Тестирование

|Пункт меню|Ввод|Ожидаемый результат|
|-|-|-|
|1. Конструкторы|`12`, `250`, `7`|`14 руб. 50 коп.`; `7 руб. 00 коп.`|
|2. Свойства|`100`, `150`|копейки отклонены|
|3. Subtract|A = `10 50`, B = `3 75`|`6 руб. 75 коп.`, `0 руб. 00 коп.`|
|4. `++` / `--`|`5 99`|`++M = 6 руб. 00 коп.`, `M++` → после `6 руб. 01 коп.`, `--M = 6 руб. 00 коп.`, `M--` → после `5 руб. 99 коп.`|
|5. Приведение|`123 45`|`unsigned int` = 123, `double` = 0.45|
|6. Бинарный минус|A = `20 30`, B = `5 20`, N = `5`|`A - B = 15 руб. 10 коп.`, `B - A = 0 руб. 00 коп.`, `A - N = 15 руб. 30 коп.`|

Скриншоты:

!\[Конструкторы и свойства](screenshots/task2\_constructors.png)

!\[Subtract](screenshots/task2\_subtract.png)

!\[++ и --](screenshots/task2\_increment.png)

!\[Приведение типов](screenshots/task2\_conversions.png)

!\[Бинарный минус](screenshots/task2\_minus.png)

<details>
<summary>Текстовый вывод программы</summary>

```

Задание 2: класс Money
1. Конструкторы
2. Свойства
3. Метод Subtract
4. Операции ++ и --
5. Приведение типов
6. Бинарный минус (Money и unsigned int)
0. Выход
Ваш выбор: 
Тест конструкторов
1) Money():                0 руб. 00 коп.
2) Money(рубли, копейки). Копейки > 99 переходят в рубли.
  рубли:   копейки (0-32767):    результат: 14 руб. 50 коп.
3) Money(рубли).
  рубли:    результат: 7 руб. 00 коп.
4) Копия пункта 2:         14 руб. 50 коп.

Задание 2: класс Money
1. Конструкторы
2. Свойства
3. Метод Subtract
4. Операции ++ и --
5. Приведение типов
6. Бинарный минус (Money и unsigned int)
0. Выход
Ваш выбор: 
Тест свойств
Начальное значение: 5 руб. 30 коп.
Новые рубли: Новые копейки (0-32767): Копейки отклонены: допустимы значения от 0 до 99.
rubles() = 100, kopeks() = 30
Итог: 100 руб. 30 коп.

Задание 2: класс Money
1. Конструкторы
2. Свойства
3. Метод Subtract
4. Операции ++ и --
5. Приведение типов
6. Бинарный минус (Money и unsigned int)
0. Выход
Ваш выбор: 
Вычитание Money: метод Subtract
Введите сумму A (уменьшаемое):
  рубли:   копейки (0-99): Введите сумму B (вычитаемое):
  рубли:   копейки (0-99): A = 10 руб. 50 коп.
B = 3 руб. 75 коп.
A.Subtract(B) = 6 руб. 75 коп.
B.Subtract(A) = 0 руб. 00 коп.  (меньше нуля быть не может)

Задание 2: класс Money
1. Конструкторы
2. Свойства
3. Метод Subtract
4. Операции ++ и --
5. Приведение типов
6. Бинарный минус (Money и unsigned int)
0. Выход
Ваш выбор: 
Операции ++ и -- 
Введите сумму M:
  рубли:   копейки (0-99): M    = 5 руб. 99 коп.
++M  = 6 руб. 00 коп.
M++  = 6 руб. 00 коп.  (после: 6 руб. 01 коп.)
--M  = 6 руб. 00 коп.
M--  = 6 руб. 00 коп.  (после: 5 руб. 99 коп.)

Задание 2: класс Money
1. Конструкторы
2. Свойства
3. Метод Subtract
4. Операции ++ и --
5. Приведение типов
6. Бинарный минус (Money и unsigned int)
0. Выход
Ваш выбор: 
Приведение типов
Введите сумму M:
  рубли:   копейки (0-99): M = 123 руб. 45 коп.
unsigned int (неявно): 123
double (явно):         0.45

Задание 2: класс Money
1. Конструкторы
2. Свойства
3. Метод Subtract
4. Операции ++ и --
5. Приведение типов
6. Бинарный минус (Money и unsigned int)
0. Выход
Ваш выбор: 
Бинарный минус
Введите сумму A:
  рубли:   копейки (0-99): Введите сумму B:
  рубли:   копейки (0-99): Целое число рублей N: A - B = 15 руб. 10 коп.
B - A = 0 руб. 00 коп.
A - N = 15 руб. 30 коп.
(если вычитаемое больше, результат равен 0)

Задание 2: класс Money
1. Конструкторы
2. Свойства
3. Метод Subtract
4. Операции ++ и --
5. Приведение типов
6. Бинарный минус (Money и unsigned int)
0. Выход
Ваш выбор: Ошибка: нужно целое число от 0 до 6. Повторите ввод.
Ваш выбор: Программа завершена.
```

</details>

# Сборка и запуск

Команды выполняются из корня репозитория (пути `#include` указаны от корня проекта, как требует Google Style):

```bash
g++ -std=c++20 -Wall -Wextra -I. -o task1\_app task1/main.cc task1/money.cc
g++ -std=c++20 -Wall -Wextra -I. -o task2\_app task2/main.cc task2/money.cc
./task1\_app
./task2\_app
```

# Соответствие Google C++ Style Guide

|Требование|Как выполнено|
|-|-|
|Свой `.h` + `.cc`, самодостаточный заголовок|у каждого задания `money.h` и `money.cc`, заголовок включает всё нужное|
|Защита от повторного включения `<PROJECT>\_<PATH>\_<FILE>\_H\_`|`LAB1\_TASK1\_MONEY\_H\_`, `LAB1\_TASK2\_MONEY\_H\_`|
|Порядок `#include`: свой заголовок, стандартная библиотека, проект|соблюдён, внутри групп по алфавиту|
|Код в пространстве имён, анонимный namespace для внутренних функций|`namespace lab1`, вспомогательные функции в `namespace { }`|
|Фигурные скобки у всех `if`/`else`/`for`/`while`/`case`|везде, без исключений|
|Переменные не объявляются внутри циклов|счётчики и буферы объявлены до цикла (требование преподавателя)|
|Имена: классы `Money`, функции `ReadNumber()`, константы `kMaxRubles`, поля `rubles\_`, геттеры `rubles()`, сеттеры `set\_rubles()`|соблюдено|
|Имена файлов в нижнем регистре, `.cc` и `.h`|`money.cc`, `money.h`, `main.cc`|
|Данные-члены `private`|оба поля закрыты, доступ через свойства|
|Исключения не используются|ошибки ввода и выхода за диапазон обрабатываются проверками и возвращаемым значением|
|Одноаргументные конструкторы и операторы приведения — `explicit`|`explicit Money(unsigned int)`, `explicit operator double()`|
|Явно объявлены операции копирования|`= default`|
|Неизменяющие бинарные операторы — не члены класса|`operator-`, `operator<<` вне класса|
|Приведения типов — C++-стиля|`static\_cast`, фигурная инициализация `int64\_t{x}`|
|Префиксный `++` там, где не нужен результат постфиксного|соблюдено|
|`const` у методов и параметров-ссылок|соблюдено|
|Комментарии у классов и функций (начинаются с глагола)|соблюдено|
|Отступ 2 пробела, строки не длиннее 80 символов|соблюдено|

**Отступления от гайда, обусловленные заданием:**

* Типы полей `unsigned int` и `short int` заданы вариантом, поэтому используются вместо `int`/`intN\_t`. Во всех остальных местах применяются `int`, `int64\_t` и `size\_t`-подобные типы.
* Неявное приведение к `unsigned int` (гайд рекомендует `explicit`) требуется вариантом задания.
* Из-за этого неявного приведения вызов `m - 5` с литералом типа `int` неоднозначен, поэтому в программе вычитаемое хранится в переменной `unsigned int` (или пишется `m - 5u`).
* Русские строки выводятся пользователю, поэтому в коде есть не-ASCII символы в кодировке UTF-8. Для Windows в `main` включена кодировка UTF-8 консоли (`SetConsoleOutputCP`, под `#ifdef \_WIN32`).

# Приложение. Исходный код

## task1/money.h

```cpp
// Задание 1 (вариант 8). Класс Money: денежная сумма в рублях и копейках.

#ifndef LAB1\_TASK1\_MONEY\_H\_
#define LAB1\_TASK1\_MONEY\_H\_

#include <cstdint>
#include <ostream>

namespace lab1 {

// Денежная сумма. Сумма не может быть отрицательной, копейки всегда лежат
// в диапазоне \[0, 99]. Класс можно копировать.
class Money {
 public:
  // Создает нулевую сумму.
  Money();

  // Создает сумму из рублей и копеек. Копейки больше 99 переводятся в рубли.
  // Отрицательные копейки считаются нулем. При переполнении рублей сумма
  // становится максимально возможной.
  Money(unsigned int rubles, short int kopeks);

  // Создает сумму из целого числа рублей.
  explicit Money(unsigned int rubles);

  Money(const Money\& other) = default;
  Money\& operator=(const Money\& other) = default;

  unsigned int rubles() const { return rubles\_; }
  short int kopeks() const { return kopeks\_; }
  void set\_rubles(unsigned int rubles) { rubles\_ = rubles; }

  // Устанавливает копейки. Возвращает false и не меняет значение, если
  // `kopeks` вне диапазона \[0, 99].
  bool set\_kopeks(short int kopeks);

  // Возвращает разность `\*this - other`. Если `other` больше `\*this`,
  // возвращает нулевую сумму, так как сумма не может быть отрицательной.
  Money Subtract(const Money\& other) const;

 private:
  // Возвращает всю сумму в копейках.
  int64\_t ToKopeks() const;

  // Создает сумму из общего количества копеек.
  static Money FromKopeks(int64\_t total\_kopeks);

  unsigned int rubles\_;
  short int kopeks\_;
};

// Выводит сумму в виде "12 руб. 05 коп.".
std::ostream\& operator<<(std::ostream\& os, const Money\& money);

}  // namespace lab1

#endif  // LAB1\_TASK1\_MONEY\_H\_
```

## task1/money.cc

```cpp
#include "task1/money.h"

#include <cstdint>
#include <limits>
#include <ostream>

namespace lab1 {

namespace {

constexpr int64\_t kKopeksInRuble = 100;
constexpr short int kMaxKopeks = 99;
constexpr unsigned int kMaxRubles = std::numeric\_limits<unsigned int>::max();

}  // namespace

Money::Money() : rubles\_(0), kopeks\_(0) {}

Money::Money(unsigned int rubles, short int kopeks) : rubles\_(0), kopeks\_(0) {
  int64\_t total = int64\_t{rubles} \* kKopeksInRuble;
  if (kopeks > 0) {
    total += kopeks;
  }
  \*this = FromKopeks(total);
}

Money::Money(unsigned int rubles) : rubles\_(rubles), kopeks\_(0) {}

bool Money::set\_kopeks(short int kopeks) {
  if (kopeks < 0 || kopeks > kMaxKopeks) {
    return false;
  }
  kopeks\_ = kopeks;
  return true;
}

Money Money::Subtract(const Money\& other) const {
  int64\_t minuend = ToKopeks();
  int64\_t subtrahend = other.ToKopeks();
  if (subtrahend >= minuend) {
    return Money();
  }
  return FromKopeks(minuend - subtrahend);
}

std::ostream\& operator<<(std::ostream\& os, const Money\& money) {
  char old\_fill = os.fill('0');
  os << money.rubles() << " руб. ";
  os.width(2);
  os << money.kopeks();
  os.fill(old\_fill);
  os << " коп.";
  return os;
}

int64\_t Money::ToKopeks() const {
  return int64\_t{rubles\_} \* kKopeksInRuble + kopeks\_;
}

Money Money::FromKopeks(int64\_t total\_kopeks) {
  Money result;
  int64\_t rubles = total\_kopeks / kKopeksInRuble;
  if (rubles > kMaxRubles) {
    result.rubles\_ = kMaxRubles;
    result.kopeks\_ = kMaxKopeks;
    return result;
  }
  result.rubles\_ = static\_cast<unsigned int>(rubles);
  result.kopeks\_ = static\_cast<short int>(total\_kopeks % kKopeksInRuble);
  return result;
}

}  // namespace lab1
```

## task1/main.cc

```cpp
// Задание 1. Консольное меню для проверки класса Money.

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include "task1/money.h"

#ifdef \_WIN32
#include <windows.h>
#endif  // \_WIN32

namespace {

using ::lab1::Money;

constexpr int64\_t kMaxRubles = 4294967295;
constexpr int64\_t kMaxKopeks = 99;
constexpr int64\_t kMaxShortKopeks = 32767;
constexpr std::string::size\_type kMaxDigits = 18;

// Returns the text without leading and trailing whitespace.
std::string Trim(const std::string\& text) {
  const std::string kSpaces = " \\t\\r\\n";
  std::string::size\_type first = text.find\_first\_not\_of(kSpaces);
  if (first == std::string::npos) {
    return "";
  }
  std::string::size\_type last = text.find\_last\_not\_of(kSpaces);
  return text.substr(first, last - first + 1);
}

// Parses a non-negative integer not greater than `max\_value`. Returns false
// if the text is not such a number; `result` is changed only on success.
bool ParseNumber(const std::string\& text, int64\_t max\_value,
                 int64\_t\* result) {
  if (text.empty() || text.size() > kMaxDigits) {
    return false;
  }
  int64\_t value = 0;
  std::string::size\_type i = 0;
  for (i = 0; i < text.size(); ++i) {
    if (text\[i] < '0' || text\[i] > '9') {
      return false;
    }
    value = value \* 10 + (text\[i] - '0');
  }
  if (value > max\_value) {
    return false;
  }
  \*result = value;
  return true;
}

// Asks for a number until a correct one is entered. Ends the program if the
// input stream is closed.
int64\_t ReadNumber(const std::string\& prompt, int64\_t max\_value) {
  std::string line;
  int64\_t value = 0;
  bool is\_correct = false;
  while (!is\_correct) {
    std::cout << prompt;
    if (!std::getline(std::cin, line)) {
      std::cout << "\\nВвод прерван.\\n";
      std::exit(EXIT\_FAILURE);
    }
    is\_correct = ParseNumber(Trim(line), max\_value, \&value);
    if (!is\_correct) {
      std::cout << "Ошибка: нужно целое число от 0 до " << max\_value
                << ". Повторите ввод.\\n";
    }
  }
  return value;
}

// Reads rubles as unsigned int.
unsigned int ReadRubles(const std::string\& prompt) {
  return static\_cast<unsigned int>(ReadNumber(prompt, kMaxRubles));
}

// Reads kopeks in the range \[0, 99].
short int ReadKopeks(const std::string\& prompt) {
  return static\_cast<short int>(ReadNumber(prompt, kMaxKopeks));
}

// Reads a whole sum (rubles and kopeks) from the keyboard.
Money ReadMoney(const std::string\& name) {
  std::cout << "Введите сумму " << name << ":\\n";
  unsigned int rubles = ReadRubles("  рубли: ");
  short int kopeks = ReadKopeks("  копейки (0-99): ");
  return Money(rubles, kopeks);
}

// Demonstrates all constructors.
void TestConstructors() {
  std::cout << "\\n--- Тест конструкторов ---\\n";
  Money by\_default;
  std::cout << "1) Money():                " << by\_default << "\\n";

  std::cout << "2) Money(рубли, копейки). Копейки > 99 переходят в рубли.\\n";
  unsigned int rubles = ReadRubles("  рубли: ");
  short int kopeks = static\_cast<short int>(
      ReadNumber("  копейки (0-32767): ", kMaxShortKopeks));
  Money two\_args(rubles, kopeks);
  std::cout << "   результат: " << two\_args << "\\n";

  std::cout << "3) Money(рубли).\\n";
  unsigned int only\_rubles = ReadRubles("  рубли: ");
  Money from\_rubles(only\_rubles);
  std::cout << "   результат: " << from\_rubles << "\\n";

  Money copy(two\_args);
  std::cout << "4) Копия пункта 2:         " << copy << "\\n";
}

// Demonstrates getters and setters.
void TestProperties() {
  std::cout << "\\n--- Тест свойств ---\\n";
  Money money(5, 30);
  std::cout << "Начальное значение: " << money << "\\n";
  unsigned int rubles = ReadRubles("Новые рубли: ");
  short int kopeks = static\_cast<short int>(
      ReadNumber("Новые копейки (0-32767): ", kMaxShortKopeks));
  money.set\_rubles(rubles);
  bool is\_set = money.set\_kopeks(kopeks);
  if (!is\_set) {
    std::cout << "Копейки отклонены: допустимы значения от 0 до 99.\\n";
  }
  std::cout << "rubles() = " << money.rubles()
            << ", kopeks() = " << money.kopeks() << "\\n";
  std::cout << "Итог: " << money << "\\n";
}

// Demonstrates the Subtract method.
void TestSubtract() {
  std::cout << "\\n--- Вычитание Money: метод Subtract ---\\n";
  Money first = ReadMoney("A (уменьшаемое)");
  Money second = ReadMoney("B (вычитаемое)");
  std::cout << "A = " << first << "\\nB = " << second << "\\n";
  std::cout << "A.Subtract(B) = " << first.Subtract(second) << "\\n";
  std::cout << "B.Subtract(A) = " << second.Subtract(first)
            << "  (меньше нуля быть не может)\\n";
}

}  // namespace

int main() {
#ifdef \_WIN32
  // Включает вывод UTF-8 в консоли Windows, чтобы русский текст читался.
  SetConsoleOutputCP(CP\_UTF8);
#endif  // \_WIN32
  bool is\_running = true;
  int64\_t choice = 0;
  while (is\_running) {
    std::cout << "\\n===== Задание 1: класс Money =====\\n"
                 "1. Конструкторы\\n"
                 "2. Свойства\\n"
                 "3. Вычитание Money (Subtract)\\n"
                 "0. Выход\\n";
    choice = ReadNumber("Ваш выбор: ", 3);
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
      default: {
        is\_running = false;
        break;
      }
    }
  }
  std::cout << "Программа завершена.\\n";
  return EXIT\_SUCCESS;
}
```

## task2/money.h

```cpp
// Задание 2 (вариант 8). Класс Money с перегруженными операциями.

#ifndef LAB1\_TASK2\_MONEY\_H\_
#define LAB1\_TASK2\_MONEY\_H\_

#include <cstdint>
#include <ostream>

namespace lab1 {

// Денежная сумма. Сумма не может быть отрицательной, копейки всегда лежат
// в диапазоне \[0, 99]. Класс можно копировать.
class Money {
 public:
  // Создает нулевую сумму.
  Money();

  // Создает сумму из рублей и копеек. Копейки больше 99 переводятся в рубли.
  // Отрицательные копейки считаются нулем. При переполнении рублей сумма
  // становится максимально возможной.
  Money(unsigned int rubles, short int kopeks);

  // Создает сумму из целого числа рублей.
  explicit Money(unsigned int rubles);

  Money(const Money\& other) = default;
  Money\& operator=(const Money\& other) = default;

  unsigned int rubles() const { return rubles\_; }
  short int kopeks() const { return kopeks\_; }
  void set\_rubles(unsigned int rubles) { rubles\_ = rubles; }

  // Устанавливает копейки. Возвращает false и не меняет значение, если
  // `kopeks` вне диапазона \[0, 99].
  bool set\_kopeks(short int kopeks);

  // Возвращает разность `\*this - other`. Если `other` больше `\*this`,
  // возвращает нулевую сумму, так как сумма не может быть отрицательной.
  Money Subtract(const Money\& other) const;

  // Добавляет одну копейку. При переполнении сумма не меняется.
  Money\& operator++();
  Money operator++(int);

  // Вычитает одну копейку. Нулевая сумма остается нулевой.
  Money\& operator--();
  Money operator--(int);

  // Неявное приведение по условию задания: количество рублей, копейки
  // отбрасываются.
  operator unsigned int() const;

  // Явное приведение: копейки, переведенные в рубли (результат меньше 1).
  explicit operator double() const;

 private:
  // Возвращает всю сумму в копейках.
  int64\_t ToKopeks() const;

  // Создает сумму из общего количества копеек.
  static Money FromKopeks(int64\_t total\_kopeks);

  unsigned int rubles\_;
  short int kopeks\_;
};

// Вычитает целое число рублей. Результат не может быть отрицательным.
Money operator-(const Money\& left, unsigned int right);

// Вычитает сумму. Результат не может быть отрицательным.
Money operator-(const Money\& left, const Money\& right);

// Выводит сумму в виде "12 руб. 05 коп.".
std::ostream\& operator<<(std::ostream\& os, const Money\& money);

}  // namespace lab1

#endif  // LAB1\_TASK2\_MONEY\_H\_
```

## task2/money.cc

```cpp
#include "task2/money.h"

#include <cstdint>
#include <limits>
#include <ostream>

namespace lab1 {

namespace {

constexpr int64\_t kKopeksInRuble = 100;
constexpr short int kMaxKopeks = 99;
constexpr unsigned int kMaxRubles = std::numeric\_limits<unsigned int>::max();

}  // namespace

Money::Money() : rubles\_(0), kopeks\_(0) {}

Money::Money(unsigned int rubles, short int kopeks) : rubles\_(0), kopeks\_(0) {
  int64\_t total = int64\_t{rubles} \* kKopeksInRuble;
  if (kopeks > 0) {
    total += kopeks;
  }
  \*this = FromKopeks(total);
}

Money::Money(unsigned int rubles) : rubles\_(rubles), kopeks\_(0) {}

bool Money::set\_kopeks(short int kopeks) {
  if (kopeks < 0 || kopeks > kMaxKopeks) {
    return false;
  }
  kopeks\_ = kopeks;
  return true;
}

Money Money::Subtract(const Money\& other) const {
  int64\_t minuend = ToKopeks();
  int64\_t subtrahend = other.ToKopeks();
  if (subtrahend >= minuend) {
    return Money();
  }
  return FromKopeks(minuend - subtrahend);
}

Money\& Money::operator++() {
  if (kopeks\_ < kMaxKopeks) {
    ++kopeks\_;
  } else if (rubles\_ < kMaxRubles) {
    ++rubles\_;
    kopeks\_ = 0;
  }
  return \*this;
}

Money Money::operator++(int) {
  Money old\_value(\*this);
  ++(\*this);
  return old\_value;
}

Money\& Money::operator--() {
  if (kopeks\_ > 0) {
    --kopeks\_;
  } else if (rubles\_ > 0) {
    --rubles\_;
    kopeks\_ = kMaxKopeks;
  }
  return \*this;
}

Money Money::operator--(int) {
  Money old\_value(\*this);
  --(\*this);
  return old\_value;
}

Money::operator unsigned int() const { return rubles\_; }

Money::operator double() const {
  return static\_cast<double>(kopeks\_) / static\_cast<double>(kKopeksInRuble);
}

Money operator-(const Money\& left, unsigned int right) {
  return left.Subtract(Money(right));
}

Money operator-(const Money\& left, const Money\& right) {
  return left.Subtract(right);
}

std::ostream\& operator<<(std::ostream\& os, const Money\& money) {
  char old\_fill = os.fill('0');
  os << money.rubles() << " руб. ";
  os.width(2);
  os << money.kopeks();
  os.fill(old\_fill);
  os << " коп.";
  return os;
}

int64\_t Money::ToKopeks() const {
  return int64\_t{rubles\_} \* kKopeksInRuble + kopeks\_;
}

Money Money::FromKopeks(int64\_t total\_kopeks) {
  Money result;
  int64\_t rubles = total\_kopeks / kKopeksInRuble;
  if (rubles > kMaxRubles) {
    result.rubles\_ = kMaxRubles;
    result.kopeks\_ = kMaxKopeks;
    return result;
  }
  result.rubles\_ = static\_cast<unsigned int>(rubles);
  result.kopeks\_ = static\_cast<short int>(total\_kopeks % kKopeksInRuble);
  return result;
}

}  // namespace lab1
```

## task2/main.cc

```cpp
// Задание 2. Консольное меню для проверки класса Money.

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>

#include "task2/money.h"

#ifdef \_WIN32
#include <windows.h>
#endif  // \_WIN32

namespace {

using ::lab1::Money;

constexpr int64\_t kMaxRubles = 4294967295;
constexpr int64\_t kMaxKopeks = 99;
constexpr int64\_t kMaxShortKopeks = 32767;
constexpr std::string::size\_type kMaxDigits = 18;

// Returns the text without leading and trailing whitespace.
std::string Trim(const std::string\& text) {
  const std::string kSpaces = " \\t\\r\\n";
  std::string::size\_type first = text.find\_first\_not\_of(kSpaces);
  if (first == std::string::npos) {
    return "";
  }
  std::string::size\_type last = text.find\_last\_not\_of(kSpaces);
  return text.substr(first, last - first + 1);
}

// Parses a non-negative integer not greater than `max\_value`. Returns false
// if the text is not such a number; `result` is changed only on success.
bool ParseNumber(const std::string\& text, int64\_t max\_value,
                 int64\_t\* result) {
  if (text.empty() || text.size() > kMaxDigits) {
    return false;
  }
  int64\_t value = 0;
  std::string::size\_type i = 0;
  for (i = 0; i < text.size(); ++i) {
    if (text\[i] < '0' || text\[i] > '9') {
      return false;
    }
    value = value \* 10 + (text\[i] - '0');
  }
  if (value > max\_value) {
    return false;
  }
  \*result = value;
  return true;
}

// Asks for a number until a correct one is entered. Ends the program if the
// input stream is closed.
int64\_t ReadNumber(const std::string\& prompt, int64\_t max\_value) {
  std::string line;
  int64\_t value = 0;
  bool is\_correct = false;
  while (!is\_correct) {
    std::cout << prompt;
    if (!std::getline(std::cin, line)) {
      std::cout << "\\nВвод прерван.\\n";
      std::exit(EXIT\_FAILURE);
    }
    is\_correct = ParseNumber(Trim(line), max\_value, \&value);
    if (!is\_correct) {
      std::cout << "Ошибка: нужно целое число от 0 до " << max\_value
                << ". Повторите ввод.\\n";
    }
  }
  return value;
}

// Reads rubles as unsigned int.
unsigned int ReadRubles(const std::string\& prompt) {
  return static\_cast<unsigned int>(ReadNumber(prompt, kMaxRubles));
}

// Reads kopeks in the range \[0, 99].
short int ReadKopeks(const std::string\& prompt) {
  return static\_cast<short int>(ReadNumber(prompt, kMaxKopeks));
}

// Reads a whole sum (rubles and kopeks) from the keyboard.
Money ReadMoney(const std::string\& name) {
  std::cout << "Введите сумму " << name << ":\\n";
  unsigned int rubles = ReadRubles("  рубли: ");
  short int kopeks = ReadKopeks("  копейки (0-99): ");
  return Money(rubles, kopeks);
}

// Demonstrates all constructors.
void TestConstructors() {
  std::cout << "\\n--- Тест конструкторов ---\\n";
  Money by\_default;
  std::cout << "1) Money():                " << by\_default << "\\n";

  std::cout << "2) Money(рубли, копейки). Копейки > 99 переходят в рубли.\\n";
  unsigned int rubles = ReadRubles("  рубли: ");
  short int kopeks = static\_cast<short int>(
      ReadNumber("  копейки (0-32767): ", kMaxShortKopeks));
  Money two\_args(rubles, kopeks);
  std::cout << "   результат: " << two\_args << "\\n";

  std::cout << "3) Money(рубли).\\n";
  unsigned int only\_rubles = ReadRubles("  рубли: ");
  Money from\_rubles(only\_rubles);
  std::cout << "   результат: " << from\_rubles << "\\n";

  Money copy(two\_args);
  std::cout << "4) Копия пункта 2:         " << copy << "\\n";
}

// Demonstrates getters and setters.
void TestProperties() {
  std::cout << "\\n--- Тест свойств ---\\n";
  Money money(5, 30);
  std::cout << "Начальное значение: " << money << "\\n";
  unsigned int rubles = ReadRubles("Новые рубли: ");
  short int kopeks = static\_cast<short int>(
      ReadNumber("Новые копейки (0-32767): ", kMaxShortKopeks));
  money.set\_rubles(rubles);
  bool is\_set = money.set\_kopeks(kopeks);
  if (!is\_set) {
    std::cout << "Копейки отклонены: допустимы значения от 0 до 99.\\n";
  }
  std::cout << "rubles() = " << money.rubles()
            << ", kopeks() = " << money.kopeks() << "\\n";
  std::cout << "Итог: " << money << "\\n";
}

// Demonstrates the Subtract method.
void TestSubtract() {
  std::cout << "\\n--- Вычитание Money: метод Subtract ---\\n";
  Money first = ReadMoney("A (уменьшаемое)");
  Money second = ReadMoney("B (вычитаемое)");
  std::cout << "A = " << first << "\\nB = " << second << "\\n";
  std::cout << "A.Subtract(B) = " << first.Subtract(second) << "\\n";
  std::cout << "B.Subtract(A) = " << second.Subtract(first)
            << "  (меньше нуля быть не может)\\n";
}
// Demonstrates ++ and --.
void TestIncrementDecrement() {
  std::cout << "\\n--- Операции ++ и -- ---\\n";
  Money money = ReadMoney("M");
  std::cout << "M    = " << money << "\\n";
  std::cout << "++M  = " << ++money << "\\n";
  std::cout << "M++  = " << money++ << "  (после: " << money << ")\\n";
  std::cout << "--M  = " << --money << "\\n";
  std::cout << "M--  = " << money-- << "  (после: " << money << ")\\n";
}

// Demonstrates conversions to unsigned int and double.
void TestConversions() {
  std::cout << "\\n--- Приведение типов ---\\n";
  Money money = ReadMoney("M");
  unsigned int whole\_rubles = money;
  double fraction = static\_cast<double>(money);
  std::cout << "M = " << money << "\\n";
  std::cout << "unsigned int (неявно): " << whole\_rubles << "\\n";
  std::cout << "double (явно):         " << fraction << "\\n";
}

// Demonstrates operator- with Money and with unsigned int.
void TestMinus() {
  std::cout << "\\n--- Бинарный минус ---\\n";
  Money first = ReadMoney("A");
  Money second = ReadMoney("B");
  unsigned int rubles = ReadRubles("Целое число рублей N: ");
  std::cout << "A - B = " << first - second << "\\n";
  std::cout << "B - A = " << second - first << "\\n";
  std::cout << "A - N = " << first - rubles << "\\n";
  std::cout << "(если вычитаемое больше, результат равен 0)\\n";
}

}  // namespace

int main() {
#ifdef \_WIN32
  // Включает вывод UTF-8 в консоли Windows, чтобы русский текст читался.
  SetConsoleOutputCP(CP\_UTF8);
#endif  // \_WIN32
  bool is\_running = true;
  int64\_t choice = 0;
  while (is\_running) {
    std::cout << "\\n===== Задание 2: класс Money =====\\n"
                 "1. Конструкторы\\n"
                 "2. Свойства\\n"
                 "3. Метод Subtract\\n"
                 "4. Операции ++ и --\\n"
                 "5. Приведение типов\\n"
                 "6. Бинарный минус (Money и unsigned int)\\n"
                 "0. Выход\\n";
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
        is\_running = false;
        break;
      }
    }
  }
  std::cout << "Программа завершена.\\n";
  return EXIT\_SUCCESS;
}
```

