#include "xcam.h"
#include "gtest/gtest.h"

TEST(camsk0, StoreLoad) {
    xcam::camsk0(0, 1);
    EXPECT_EQ(1, xcam::camlk0(0));
}
