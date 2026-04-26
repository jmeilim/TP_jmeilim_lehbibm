#include <string> 
#include <iostream>
#include "../src/Lab4.cxx"
#include "../src/Lab3.cxx"
#include "../src/Lab6.cxx"
#include "../src/Lab2.cxx"
#include <gtest/gtest.h>


TEST(BoundaryTest, ReflexionX) {
    Particle p(Vector(-1.0, 5.0), Vector(2.0, 0.0), 1.0, 0, Vector(0,0), "A");

    conditionLimites(p, 10.0, 10.0, REFLEXION);

    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 1.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(), -2.0);
}

TEST(BoundaryTest, ReflexionCoin) {
    Particle p(Vector(-1.0, -2.0), Vector(1.0, 2.0),
               1.0, 0, Vector(0.0, 0.0), "A");

    conditionLimites(p, 10.0, 10.0, REFLEXION);

    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 1.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 2.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(), -1.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(), -2.0);
}