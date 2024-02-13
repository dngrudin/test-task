
#include "testTop5.hpp"

namespace utest {

void registerTop5Test(const std::vector<TestData> &testDataList, std::size_t maxCountThreads) {
  for (const auto &testData : testDataList) {
    testing::RegisterTest("Top5Test", ("Test: " + testData.desc).c_str(), nullptr, "", __FILE__,
                          __LINE__, [=]() { return new Top5Test(testData, maxCountThreads); });
  }
}

void Top5Fixture::SetUp() { fillMatrix(mMatrix); }

void Top5Fixture::TearDown() {
  mMatrix.clear();
  mMatrix.shrink_to_fit();
}

const top5::Matrix &Top5Fixture::getMatrix() const { return mMatrix; }

Top5Test::Top5Test(TestData testData, std::size_t maxCountThreads)
    : mTestData(std::move(testData)), mMaxCountThreads(maxCountThreads) {}

void Top5Test::TestBody() {
  for (std::size_t i = 1; i <= mMaxCountThreads; ++i) {
    auto top5 = top5::getTop5(getMatrix(), i);
    ASSERT_EQ(top5, mTestData.wantedResualt);
  }
}

void Top5Test::fillMatrix(top5::Matrix &matrix) {
  matrix.reserve(mTestData.matrixSize);
  for (std::size_t i = 0; i < mTestData.matrixSize; ++i) {
    matrix.emplace_back(mTestData.valueGenerator(i));
  }
}

} // namespace utest