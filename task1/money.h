// Задание 1 (вариант 8). Класс Money: денежная сумма в рублях и копейках.

#ifndef LAB1_TASK1_MONEY_H_
#define LAB1_TASK1_MONEY_H_

#include <cstdint>
#include <ostream>

namespace lab1 {

class Money {
 public:
  Money();

  Money(unsigned int rubles, short int kopeks);

  explicit Money(unsigned int rubles);

  Money(const Money& other) = default;
  Money& operator=(const Money& other) = default;

  unsigned int rubles() const { return rubles_; }
  short int kopeks() const { return kopeks_; }
  void set_rubles(unsigned int rubles) { rubles_ = rubles; }

  bool set_kopeks(short int kopeks);

  Money Subtract(const Money& other) const;

 private:
  int64_t ToKopeks() const;

  static Money FromKopeks(int64_t total_kopeks);

  unsigned int rubles_;
  short int kopeks_;
};

std::ostream& operator<<(std::ostream& os, const Money& money);

}

#endif  //