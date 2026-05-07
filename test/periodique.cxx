#include <gtest/gtest.h>
#include "../include/Particle.hxx"
#include "../include/Boundary.hxx"
#include "../include/Vector.hxx"

// ── Tests periodique() ─────────────────────────────────

TEST(PeriodiqueTest, GaucheTeleporte) {
    Particle p(Vector(-1.0, 5.0), Vector(2.0, 0.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    periodique(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 9.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(),  2.0); // vitesse inchangée
}

TEST(PeriodiqueTest, DroiteTeleporte) {
    Particle p(Vector(11.0, 5.0), Vector(2.0, 0.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    periodique(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 1.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(),  2.0);
}

TEST(PeriodiqueTest, BasTeleporte) {
    Particle p(Vector(5.0, -1.0), Vector(0.0, 2.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    periodique(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 9.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(),  2.0);
}

TEST(PeriodiqueTest, HautTeleporte) {
    Particle p(Vector(5.0, 11.0), Vector(0.0, 2.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    periodique(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 1.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(),  2.0);
}

TEST(PeriodiqueTest, CoinBasGauche) {
    Particle p(Vector(-1.0, -2.0), Vector(1.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    periodique(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 9.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 8.0);
}

TEST(PeriodiqueTest, InterieurInchange) {
    Particle p(Vector(5.0, 5.0), Vector(1.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");
    periodique(p, 10.0, 10.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 5.0);
    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 5.0);
}