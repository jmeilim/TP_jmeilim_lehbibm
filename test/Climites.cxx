#include <gtest/gtest.h>
#include "../include/Particle.hxx"
#include "../include/Boundary.hxx"
#include "../include/Vector.hxx"

TEST(ConditionLimitesTest, AbsorptionHaut) {
    Particle p(Vector(5.0, 11.0), Vector(0.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    bool alive = conditionLimites(p, 10.0, 10.0);
    EXPECT_FALSE(alive);
    EXPECT_FALSE(p.isAlive());
}

TEST(ConditionLimitesTest, ReflexionBas) {
    Particle p(Vector(5.0, -2.0), Vector(1.0, -3.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    conditionLimites(p, 10.0, 10.0);
    EXPECT_NEAR(p.getPosition().getY(), 1e-3, 1e-9); 
    EXPECT_NEAR(p.getVitesse().getY(),  3.0,  1e-9);
}

TEST(ConditionLimitesTest, ReflexionGauche) {
    Particle p(Vector(-2.0, 5.0), Vector(-3.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    conditionLimites(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(),  2.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(),   3.0);
}

TEST(ConditionLimitesTest, ReflexionDroite) {
    Particle p(Vector(12.0, 5.0), Vector(3.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    conditionLimites(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(),  8.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(),  -3.0);
}

TEST(ConditionLimitesTest, InterieurInchange) {
    Particle p(Vector(5.0, 5.0), Vector(1.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    bool alive = conditionLimites(p, 10.0, 10.0);
    EXPECT_TRUE(alive);
    EXPECT_TRUE(p.isAlive());
    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 5.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 5.0);
}

TEST(ConditionLimitesTest, CoinHautDroiteAbsorbe) {
    Particle p(Vector(11.0, 12.0), Vector(1.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    bool alive = conditionLimites(p, 10.0, 10.0);
    EXPECT_FALSE(alive);
    EXPECT_FALSE(p.isAlive());
}