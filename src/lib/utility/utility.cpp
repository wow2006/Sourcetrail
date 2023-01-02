#include "utility.h"

constexpr auto Digit = 10;

size_t utility::digits(size_t number) {
  int digits = 1;

  while(number >= Digit) {
    number /= Digit;
    digits++;
  }

  return static_cast<size_t>(digits);
}
