
#ifndef UTILITIES_H
#define UTILITIES_H

#include <future>
#include <map>
#include <unordered_map>

#include "numbers_type_array.hpp"

namespace top5 {

namespace detail {

static constexpr Value MAX_VALUE =
    1000; /** < Maximum value that will be taken into account in the calculation */
static constexpr std::size_t MIN_SIZE_ON_THREAD =
    100; /** < Minimum number of values to calculate in one thread */
static constexpr std::size_t MAX_RETUN_SIZE =
    5; /** < Maximum number of return values with different frequency of occurrence */

} // namespace detail

/**
 * @brief Helper types.
 */
using Counter = std::uint64_t; /** < Type to store the number of occurrences of a value */
using NumbersFrequency = std::unordered_map<Value, Counter>; /** < Type to store the number of
                                                                occurrences for multiple values */
using FrequencySortedNumber =
    std::map<Counter, std::set<Value>, std::greater<Counter>>; /** < Type for storing values sorted
                                                                  by frequency of occurrence */

/**
 * @brief Determines if a number is prime (numbers must be between 0 and detail::MAX_VALUE).
 *
 * @param value - input number
 * @return true if value is prime, otherwise false
 */
inline bool isPrimeNumber(Value value) {
  static constexpr auto numbersTypeArray = getNumbersTypeArray<detail::MAX_VALUE>();
  return value <= detail::MAX_VALUE ? numbersTypeArray[value] : false;
}

/**
 * @brief Calculates the frequency of occurrence of data in a set within a given range.
 *
 * @param matrix - input dataset
 * @param from - start of range from set
 * @param to - end of range from set
 * @param numbersFrequency - calculation result
 */
static void calculateNumbersFrequency(const Matrix &matrix, std::size_t from, std::size_t to,
                                      NumbersFrequency &numbersFrequency) {
  for (std::size_t i = from; i < to; ++i) {
    const auto &value = matrix[i];
    if (isPrimeNumber(value)) {
      numbersFrequency[value]++;
    }
  }
}

/**
 * @brief Divides the data into separate sets and runs the computation of each set in a separate
 * thread.
 *
 * @param matrix - input dataset
 * @param partialNumbersFrequencies - calculation result for each set
 */
static void mapData(const Matrix &matrix,
                    std::vector<NumbersFrequency> &partialNumbersFrequencies) {
  if (!partialNumbersFrequencies.empty()) {
    const std::size_t step = matrix.size() / partialNumbersFrequencies.size();
    std::size_t from = 0;
    std::size_t to = step;

    std::vector<std::future<void>> futures{};
    futures.reserve(partialNumbersFrequencies.size());
    for (std::size_t i = 0; i < partialNumbersFrequencies.size(); ++i) {
      futures.emplace_back(std::async(std::launch::async, calculateNumbersFrequency,
                                      std::cref(matrix), from, to,
                                      std::ref(partialNumbersFrequencies[i])));

      from = to;
      to += step;
      if (to >= matrix.size()) {
        to = matrix.size() - 1;
      }
    }

    /// waiting for all calculations to complete
    for (const auto &future : futures) {
      future.wait();
    }
  }
}

/**
 * @brief Combines frequencies from several sets into one.
 *
 * @param partialNumbersFrequencies - frequencies for each set
 * @param tottalNumbersFrequency - tottal set of frequencies
 */
static void reduceData(const std::vector<NumbersFrequency> &partialNumbersFrequencies,
                       NumbersFrequency &tottalNumbersFrequency) {
  for (const auto &partialNumbersFrequency : partialNumbersFrequencies) {
    for (const auto &[value, counter] : partialNumbersFrequency) {
      tottalNumbersFrequency[value] += counter;
    }
  }
}

/**
 * @brief Converts the frequency for each value into a group of values with the same frequency.
 *
 * @param numbersFrequency - list of frequency for each value
 * @return groups of values with the same frequency
 */
static FrequencySortedNumber
convertToFrequencySortedNumber(const NumbersFrequency &numbersFrequency) {
  FrequencySortedNumber sortValuesNumber{};
  for (const auto &[value, counter] : numbersFrequency) {
    sortValuesNumber[counter].emplace(value);
  }
  return sortValuesNumber;
}

/**
 * @brief Filters the data and returns the first 5 values.
 *
 * @param frequencySortedNumber - groups of values with the same frequency
 * @return the first 5 top frequently occurring values
 */
static Top5Result preperaResult(FrequencySortedNumber &frequencySortedNumber) {
  Top5Result top5{};

  const std::size_t resultSize = std::min(detail::MAX_RETUN_SIZE, frequencySortedNumber.size());
  auto currentItem = frequencySortedNumber.begin();
  for (std::size_t i = 0; i < resultSize; ++i) {
    top5.emplace_back(std::move(currentItem->second));
    ++currentItem;
  }

  return top5;
}

} // namespace top5

#endif // UTILITIES_H