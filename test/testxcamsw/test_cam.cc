#include "xcam.h"
#include "gtest/gtest.h"

TEST(cam, Hello) {
    xcam::cams(0, {{0x100, 0x20a}, 0x300});
    xcam::cams(1, {{0x100, 0x21a}, 0x400});

    EXPECT_EQ(0x31b, xcam::cam<8>({0x100, 0x21b}));
    EXPECT_EQ(0x40b, xcam::cam<4>({0x100, 0x21b}));
    EXPECT_EQ(0x000, xcam::cam<8>({0x200, 0x21b}));
    EXPECT_EQ(0x000, xcam::cam<10>({0x200, 0x21b}));
}
