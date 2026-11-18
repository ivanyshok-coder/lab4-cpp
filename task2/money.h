// Задание 2 (вариант 8). Класс Money с перегруженными операциями.

#ifndef LAB1_TASK2_MONEY_H_
#define LAB1_TASK2_MONEY_H_

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

  Money& operator++();
  Money operator++(int);

  Money& operator--();
  Money operator--(int);

  operator unsigned int() const;

  explicit operator double() const;

 private:

  int64_t ToKopeks() const;

  static Money FromKopeks(int64_t total_kopeks);

  unsigned int rubles_;
  short int kopeks_;
};

Money operator-(const Money& left, unsigned int right);

Money operator-(const Money& left, const Money& right);

std::ostream& operator<<(std::ostream& os, const Money& money);

}  // namespace lab1

#endif  // LAB1_TASK2_MONEY_H_
