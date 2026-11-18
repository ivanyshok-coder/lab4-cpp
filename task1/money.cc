#include "task1/money.h"

#include <cstdint>
#include <limits>
#include <ostream>

namespace lab1 {

namespace {

constexpr int64_t kKopeksInRuble = 100;
constexpr short int kMaxKopeks = 99;
constexpr unsigned int kMaxRubles = std::numeric_limits<unsigned int>::max();

}  // namespace

Money::Money() : rubles_(0), kopeks_(0) {}

Money::Money(unsigned int rubles, short int kopeks) : rubles_(0), kopeks_(0) {
  int64_t total = int64_t{rubles} * kKopeksInRuble;
  if (kopeks > 0) {
    total += kopeks;
  }
  *this = FromKopeks(total);
}

Money::Money(unsigned int rubles) : rubles_(rubles), kopeks_(0) {}

bool Money::set_kopeks(short int kopeks) {
  if (kopeks < 0 || kopeks > kMaxKopeks) {
    return false;
  }
  kopeks_ = kopeks;
  return true;
}

Money Money::Subtract(const Money& other) const {
  int64_t minuend = ToKopeks();
  int64_t subtrahend = other.ToKopeks();
  if (subtrahend >= minuend) {
    return Money();
  }
  return FromKopeks(minuend - subtrahend);
}

std::ostream& operator<<(std::ostream& os, const Money& money) {
  char old_fill = os.fill('0');
  os << money.rubles() << " руб. ";
  os.width(2);
  os << money.kopeks();
  os.fill(old_fill);
  os << " коп.";
  return os;
}

int64_t Money::ToKopeks() const {
  return int64_t{rubles_} * kKopeksInRuble + kopeks_;
}

Money Money::FromKopeks(int64_t total_kopeks) {
  Money result;
  int64_t rubles = total_kopeks / kKopeksInRuble;
  if (rubles > kMaxRubles) {
    result.rubles_ = kMaxRubles;
    result.kopeks_ = kMaxKopeks;
    return result;
  }
  result.rubles_ = static_cast<unsigned int>(rubles);
  result.kopeks_ = static_cast<short int>(total_kopeks % kKopeksInRuble);
  return result;
}

}  // namespace lab1
