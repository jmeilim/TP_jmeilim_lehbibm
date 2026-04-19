#include <string> 
#include <iostream>
#include "../src/Lab4.cxx"
#include <gtest/gtest.h>




TEST(UniversTest, Initialisation) {
    Univers u(1.0, 2.0, 3, 10.0, 2.5);

    EXPECT_EQ(u.dim, 3);
    EXPECT_DOUBLE_EQ(u.eps, 1.0);
}

TEST(UniversTest, ValeursValides) {
    Univers u(1.0, 2.0, 3, 10.0, 2.5);

    EXPECT_TRUE(u.rc > 0);
}