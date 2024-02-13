
#include <climits>
#include <cstdlib>
#include <ctime>

#include "DataPull.hpp"

namespace {

int randBetween(int min, int max) { return min + rand() % (max - min + 1); }

} // namespace

DataPull::DataPull(size_t size) : mDataPull(size) { srand(time(NULL)); }

const std::vector<int16_t> &DataPull::get(size_t index) const {
  return mDataPull[index];
}

size_t DataPull::count() const { return mDataPull.size(); }

void DataPull::generate() {
  for (size_t i = 0; i < mDataPull.size(); ++i) {
    std::vector<int16_t> &data = mDataPull[i];
    data.resize(randBetween(600, 1600));
    fill(data);
  }
}

void DataPull::fill(std::vector<int16_t> &data) {
  for (size_t i = 0; i < data.size(); ++i) {
    data[i] = randBetween(SHRT_MIN, SHRT_MAX);
  }
}