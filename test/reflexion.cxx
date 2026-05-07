#include <gtest/gtest.h>
#include "../include/Particle.hxx"
#include "../include/Boundary.hxx"
#include "../include/Vector.hxx"

// ── Tests reflexion() ──────────────────────────────────

TEST(ReflexionTest, ReflexionBas) {
    Particle p(Vector(5.0, -2.0), Vector(1.0, -3.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    reflexion(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(),  2.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(),   3.0);
}

TEST(ReflexionTest, ReflexionHaut) {
    Particle p(Vector(5.0, 12.0), Vector(1.0, 2.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    reflexion(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(),  8.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(),  -2.0);
}

TEST(ReflexionTest, ReflexionGauche) {
    Particle p(Vector(-2.0, 5.0), Vector(-3.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    reflexion(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(),  2.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(),   3.0);
}

TEST(ReflexionTest, ReflexionDroite) {
    Particle p(Vector(12.0, 5.0), Vector(3.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    reflexion(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(),  8.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(),  -3.0);
}

TEST(ReflexionTest, CoinBasGauche) {
    Particle p(Vector(-2.0, -3.0), Vector(-1.0, -2.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    reflexion(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(),  2.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(),  3.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(),   1.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(),   2.0);
}

TEST(ReflexionTest, InterieurInchange) {
    Particle p(Vector(5.0, 5.0), Vector(1.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    reflexion(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 5.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 5.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(),  1.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(),  1.0);
}