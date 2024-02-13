#ifndef NUMBER_TYPE_ARRAY_H
#define NUMBER_TYPE_ARRAY_H

#include <array>

#include "types.hpp"

namespace top5 {
/**
 * @brief Calculates whether a number is prime or not.
 *
 * @param number - input number
 * @return true if number is prime, otherwise false
 */
constexpr bool calculetIsNumberPrime(Value number) {
  bool isPrime = (number == 0) ? false : true;

  for (std::uint16_t i = 2; i * i <= number; ++i) {
    if (number % i == 0) {
      isPrime = false;
      break;
    }
  }
  return isPrime;
}

/**
 * @brief Creates an array at compile time with information about whether a number from a list is
 * prime or not.
 *
 * @tparam Numbers - list of number to calculate
 * @return array with the information whether a number is prime or not
 */
template <Value... Numbers>
constexpr auto createNumbersTypeArray(std::integer_sequence<Value, Numbers...>) {
  constexpr std::array<bool, sizeof...(Numbers)> arrayNumbersType{
      calculetIsNumberPrime(Numbers)...};
  return arrayNumbersType;
}

/**
 * @brief Calculates an array at compile time with information about whether a number in a range is
 * prime or not.
 *
 * @tparam MaxNumber - maximum value in the calculation range
 * @return array with the information whether a number is prime or not
 */
template <Value MaxNumber, typename Numbers = std::make_integer_sequence<Value, MaxNumber + 1>>
constexpr auto getNumbersTypeArray() {
  return createNumbersTypeArray(Numbers{});
}

} // namespace top5

#endif // NUMBER_TYPE_ARRAY_H