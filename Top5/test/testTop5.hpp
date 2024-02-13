
#ifndef TEST_TOP_5_H
#define TEST_TOP_5_H

#include <functional>
#include <string>

#include <gtest/gtest.h>

#include "top5.hpp"

namespace utest {

struct TestData {
  using ValueGenerator = std::function<top5::Value(std::size_t)>;

  std::string desc;

  std::size_t matrixSize;
  ValueGenerator valueGenerator;
  top5::Top5Result wantedResualt;
};

class Top5Fixture : public testing::Test {
public:
  static void SetUpTestSuite() {}
  static void TearDownTestSuite() {}

  void SetUp() override;

  void TearDown() override;

  const top5::Matrix &getMatrix() const;

protected:
  virtual void fillMatrix(top5::Matrix &matrix) = 0;

private:
  top5::Matrix mMatrix;
};

class Top5Test : public Top5Fixture {
public:
  explicit Top5Test(TestData testData, std::size_t maxCountThreads);

  void TestBody() override;

  void fillMatrix(top5::Matrix &matrix) override;

private:
  TestData mTestData;
  std::size_t mMaxCountThreads;
};

void registerTop5Test(const std::vector<TestData> &testDataList, std::size_t maxCountThreads);

} // namespace utest

#endif // TEST_TOP_5_H
