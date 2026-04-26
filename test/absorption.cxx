#include <string> 
#include <iostream>
#include "../src/Lab4.cxx"
#include "../src/Lab3.cxx"
#include "../src/Lab6.cxx"
#include "../src/Lab2.cxx"
#include <gtest/gtest.h>

TEST(BoundaryTest, AbsorptionCoin) {
    Particle p(Vector(-1.0, -1.0), Vector(0.0, 0.0),
               1.0, 0, Vector(0.0, 0.0), "A");

    conditionLimites(p, 10.0, 10.0, ABSORPTION);

    EXPECT_FALSE(p.isAlive());
}