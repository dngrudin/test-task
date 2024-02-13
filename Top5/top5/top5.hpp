
#ifndef TOP_5_H
#define TOP_5_H

#include <set>
#include <vector>

#include "types.hpp"

namespace top5 {
/**
 * @brief Calculates the 5 top frequent primes in a set in multiple threads.
 *
 * @param matrix - input dataset
 * @param maxCountThreads - maximum number of threads to use for calculation
 * @return the first 5 top frequently occurring primes in a matrix
 */
Top5Result getTop5(const Matrix &matrix, std::size_t maxCountThreads = 1);

/**
 * @brief Getter for the maximum value that will be taken into account in the calculation the 5 top
 * frequent primes.
 *
 * @return the maximum avalible value for calculation
 */
Value getMaxAvalibleValue();

} // namespace top5

#endif // TOP_5_H