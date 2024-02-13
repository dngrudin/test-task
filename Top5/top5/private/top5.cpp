
#include "top5.hpp"
#include "utilites.hpp"

namespace top5 {

Top5Result getTop5(const Matrix &matrix, std::size_t maxCountThreads) {
  NumbersFrequency tottalNumbersFrequency{};

  /// calculate the actual required number of threads
  maxCountThreads = std::min(maxCountThreads, matrix.size() / detail::MIN_SIZE_ON_THREAD);

  if (maxCountThreads < 2) /// calculation in one thread
  {
    /// calculates the frequency of occurrence
    calculateNumbersFrequency(matrix, 0, matrix.size(), tottalNumbersFrequency);
  } else {
    std::vector<NumbersFrequency> partialNumbersFrequencies(maxCountThreads);
    /// divides the data into separate sets and runs the computation of each set in a separate
    /// thread
    mapData(matrix, partialNumbersFrequencies);

    /// combines frequencies from several sets into one
    reduceData(partialNumbersFrequencies, tottalNumbersFrequency);
  }

  /// converts the frequency for each value into a group of values with the same frequency
  FrequencySortedNumber frequencySortedNumber =
      convertToFrequencySortedNumber(tottalNumbersFrequency);

  /// filters the data and returns the first 5 values
  return preperaResult(frequencySortedNumber);
}

Value getMaxAvalibleValue() { return detail::MAX_VALUE; }

} // namespace top5