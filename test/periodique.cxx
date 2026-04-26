#include <string> 
#include <iostream>
#include "../src/Lab4.cxx"
#include "../src/Lab3.cxx"
#include "../src/Lab6.cxx"
#include "../src/Lab2.cxx"
#include <gtest/gtest.h>

TEST(BoundaryTest, PeriodiqueY) {
    Particle p(Vector(5.0, -1.0), Vector(0.0, 2.0),
               1.0, 0, Vector(0.0, 0.0), "A");

    conditionLimites(p, 10.0, 10.0, PERIODIQUE);

    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 9.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(), 2.0);
}

TEST(BoundaryTest, PeriodiqueCoin) {
    Particle p(Vector(-1.0, 11.0), Vector(1.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");

    conditionLimites(p, 10.0, 10.0, PERIODIQUE);

    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 9.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 1.0);
}