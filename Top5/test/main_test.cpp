
#include <gtest/gtest.h>

#include "testTop5.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  constexpr std::size_t MAX_COUNT_THREAD = 5;

  const std::vector<utest::TestData> testDataList{
      {"Same frequency (0 - 9)", 10 * 100000,
       [](std::size_t position) { return top5::Value(position % 10); },
       top5::Top5Result{{1, 2, 3, 5, 7}}},
      {"Different frequency", 450 * 10000,
       [](std::size_t position) {
         position = position % 10000;

         if (position >= 0 && position < 10) {
           return top5::Value(1);
         } else if (position >= 10 && position < 30) {
           return top5::Value(2);
         } else if (position >= 30 && position < 60) {
           return top5::Value(3);
         } else if (position >= 60 && position < 100) {
           return top5::Value(4);
         } else if (position >= 100 && position < 150) {
           return top5::Value(5);
         } else if (position >= 150 && position < 210) {
           return top5::Value(6);
         } else if (position >= 210 && position < 280) {
           return top5::Value(7);
         } else if (position >= 280 && position < 360) {
           return top5::Value(8);
         } else if (position >= 360 && position < 450) {
           return top5::Value(11);
         }

         return top5::Value(0);
       },
       top5::Top5Result{{11}, {7}, {5}, {3}, {2}}},
      {"Partly different frequency", 540 * 10000,
       [](std::size_t position) {
         position = position % 10000;

         if (position >= 0 && position < 10) {
           return top5::Value(1);
         } else if (position >= 10 && position < 30) {
           return top5::Value(2);
         } else if (position >= 30 && position < 60) {
           return top5::Value(3);
         } else if (position >= 60 && position < 100) {
           return top5::Value(4);
         } else if (position >= 100 && position < 150) {
           return top5::Value(5);
         } else if (position >= 150 && position < 210) {
           return top5::Value(6);
         } else if (position >= 210 && position < 280) {
           return top5::Value(7);
         } else if (position >= 280 && position < 360) {
           return top5::Value(8);
         } else if (position >= 360 && position < 450) {
           return top5::Value(11);
         } else if (position >= 450 && position < 540) {
           return top5::Value(13);
         }

         return top5::Value(0);
       },
       top5::Top5Result{{11, 13}, {7}, {5}, {3}, {2}}}};

  registerTop5Test(testDataList, MAX_COUNT_THREAD);
  return RUN_ALL_TESTS();
}