#include <string> 
#include <iostream>
#include <gtest/gtest.h>

#include "../include/Particle.hxx"
#include "../include/Vector.hxx"
#include "../include/Cellule.hxx"
#include "../include/Stromer.hxx"
#include "../include/Forces.hxx"
#include "../include/Univers.hxx"
#include "../include/Boundary.hxx"
TEST(BoundaryTest, AbsorptionTop) {
    Particle p(Vector(5.0, 11.0), Vector(0.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");

    bool alive = conditionLimites(p, 10.0, 10.0);

    EXPECT_FALSE(alive);
    EXPECT_FALSE(p.isAlive());
}

// ==============================
// Réflexion en bas
// ==============================
TEST(BoundaryTest, ReflexionBas) {
    Particle p(Vector(5.0, -2.0), Vector(1.0, -3.0),
               1.0, 0, Vector(0.0, 0.0), "A");

    conditionLimites(p, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 2.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(), 3.0);
}

// ==============================
// Périodique en X (gauche)
// ==============================
TEST(BoundaryTest, PeriodiqueXGauche) {
    Particle p(Vector(-1.0, 5.0), Vector(2.0, 0.0),
               1.0, 0, Vector(0,0), "A");

    conditionLimites(p, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 9.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(), 2.0);
}

// ==============================
// Périodique en X (droite)
// ==============================
TEST(BoundaryTest, PeriodiqueXDroite) {
    Particle p(Vector(11.0, 5.0), Vector(2.0, 0.0),
               1.0, 0, Vector(0,0), "A");

    conditionLimites(p, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 1.0);
    EXPECT_DOUBLE_EQ(p.getVitesse().getX(), 2.0);
}

// ==============================
// Coin : périodique X + réflexion Y
// ==============================
TEST(BoundaryTest, CoinBasGauche) {
    Particle p(Vector(-1.0, -2.0), Vector(1.0, -2.0),
               1.0, 0, Vector(0.0, 0.0), "A");

    conditionLimites(p, 10.0, 10.0);

    EXPECT_DOUBLE_EQ(p.getPosition().getX(), 9.0); // périodique
    EXPECT_DOUBLE_EQ(p.getPosition().getY(), 2.0); // réflexion
    EXPECT_DOUBLE_EQ(p.getVitesse().getY(), 2.0);  // inversion
}

// ==============================
// Coin haut : périodique X + absorption Y
// ==============================
TEST(BoundaryTest, CoinHautDroite) {
    Particle p(Vector(11.0, 12.0), Vector(1.0, 1.0),
               1.0, 0, Vector(0.0, 0.0), "A");

    bool alive = conditionLimites(p, 10.0, 10.0);

    EXPECT_FALSE(alive);
    EXPECT_FALSE(p.isAlive());
}