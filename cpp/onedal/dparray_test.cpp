#include "gtest/gtest.h"
#include "onedal/dparray.hpp"

using namespace dal;
using std::int32_t;

TEST(dparray_test, test) {
    dparray<float> arr;
    ASSERT_EQ(arr.get_data(), nullptr);
    ASSERT_EQ(arr.get_size(), 0);
}
