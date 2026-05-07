#include <gtest/gtest.h>
#include "../include/Particle.hxx"
#include "../include/Boundary.hxx"
#include "../include/Vector.hxx"

// ── Tests absorption() ─────────────────────────────────

TEST(AbsorptionTest, HautAbsorbe) {
    Particle p(Vector(5.0, 11.0), Vector(0.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    absorption(p, 10.0, 10.0);
    EXPECT_FALSE(p.isAlive());
}

TEST(AbsorptionTest, BasAbsorbe) {
    Particle p(Vector(5.0, -1.0), Vector(0.0, -1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    absorption(p, 10.0, 10.0);
    EXPECT_FALSE(p.isAlive());
}

TEST(AbsorptionTest, GaucheAbsorbe) {
    Particle p(Vector(-1.0, 5.0), Vector(-1.0, 0.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    absorption(p, 10.0, 10.0);
    EXPECT_FALSE(p.isAlive());
}

TEST(AbsorptionTest, DroiteAbsorbe) {
    Particle p(Vector(11.0, 5.0), Vector(1.0, 0.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    absorption(p, 10.0, 10.0);
    EXPECT_FALSE(p.isAlive());
}

TEST(AbsorptionTest, InterieurVivant) {
    Particle p(Vector(5.0, 5.0), Vector(1.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    absorption(p, 10.0, 10.0);
    EXPECT_TRUE(p.isAlive());
}

TEST(AbsorptionTest, CoinHautDroiteAbsorbe) {
    Particle p(Vector(11.0, 12.0), Vector(1.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    absorption(p, 10.0, 10.0);
    EXPECT_FALSE(p.isAlive());
}