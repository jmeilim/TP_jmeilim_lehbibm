#include <gtest/gtest.h>
#include "../include/Particle.hxx"
#include "../include/Vector.hxx"
#include "../include/Cellule.hxx"
#include "../include/Forces.hxx"
#include "../include/Univers.hxx"
#include <cmath>

// ── Tests computeForce ─────────────────────────────────

TEST(ForcesTest, ForceNulleSiSeule) {
    Univers u(1.0, 1.0, 2, 10.0, 10.0, 2.5);
    u.addParticle(Particle(Vector(5.0, 5.0), Vector(0,0),
                           1.0, 0, Vector(0,0), "disk"));
    u.updateCells();
    Vector F = computeForce(
        u.getParticles()[0], u.getParticles(),
        u.getRc(), u.getGrid(),
        u.getCellSize(), u.getNx(), u.getNy()
    );
    EXPECT_NEAR(F[0],   0.0, 1e-10); // pas de force en X
    EXPECT_NEAR(F[1], -12.0, 1e-10); // gravité seule : m*G = 1*(-12)
}

TEST(ForcesTest, ForceRepulsiveProche) {
    Univers u(1.0, 1.0, 2, 10.0, 10.0, 2.5);
    u.addParticle(Particle(Vector(5.0, 5.0), Vector(0,0),
                           1.0, 0, Vector(0,0), "disk"));
    u.addParticle(Particle(Vector(5.5, 5.0), Vector(0,0),
                           1.0, 1, Vector(0,0), "disk"));
    u.updateCells();
    Vector F = computeForce(
        u.getParticles()[0], u.getParticles(),
        u.getRc(), u.getGrid(),
        u.getCellSize(), u.getNx(), u.getNy()
    );
 
    EXPECT_LT(F[0], 0.0);
}

TEST(ForcesTest, ForceSymetrique) {
    Univers u(1.0, 1.0, 2, 10.0, 10.0, 2.5);
    u.addParticle(Particle(Vector(4.0, 5.0), Vector(0,0),
                           1.0, 0, Vector(0,0), "disk"));
    u.addParticle(Particle(Vector(6.0, 5.0), Vector(0,0),
                           1.0, 1, Vector(0,0), "disk"));
    u.updateCells();
    Vector F0 = computeForce(
        u.getParticles()[0], u.getParticles(),
        u.getRc(), u.getGrid(),
        u.getCellSize(), u.getNx(), u.getNy()
    );
    Vector F1 = computeForce(
        u.getParticles()[1], u.getParticles(),
        u.getRc(), u.getGrid(),
        u.getCellSize(), u.getNx(), u.getNy()
    );
  
    EXPECT_NEAR(F0[0], -F1[0], 1e-10);
 
    EXPECT_NEAR(F0[1] - (-12.0), -(F1[1] - (-12.0)), 1e-10);
}

TEST(ForcesTest, ForceNulleAuDela_rc) {
    Univers u(1.0, 1.0, 2, 20.0, 20.0, 2.5);
    u.addParticle(Particle(Vector(1.0,  1.0),  Vector(0,0),
                           1.0, 0, Vector(0,0), "disk"));
    u.addParticle(Particle(Vector(10.0, 10.0), Vector(0,0),
                           1.0, 1, Vector(0,0), "disk"));
    u.updateCells();
    Vector F = computeForce(
        u.getParticles()[0], u.getParticles(),
        u.getRc(), u.getGrid(),
        u.getCellSize(), u.getNx(), u.getNy()
    );
    EXPECT_NEAR(F[0],   0.0, 1e-10); // pas d'interaction LJ en X
    EXPECT_NEAR(F[1], -12.0, 1e-10); // gravité seule : m*G = 1*(-12)
}

TEST(ForcesTest, ForceAxialeUniquement) {
    Univers u(1.0, 1.0, 2, 10.0, 10.0, 2.5);
    u.addParticle(Particle(Vector(5.0, 4.0), Vector(0,0),
                           1.0, 0, Vector(0,0), "disk"));
    u.addParticle(Particle(Vector(5.0, 6.0), Vector(0,0),
                           1.0, 1, Vector(0,0), "disk"));
    u.updateCells();
    Vector F = computeForce(
        u.getParticles()[0], u.getParticles(),
        u.getRc(), u.getGrid(),
        u.getCellSize(), u.getNx(), u.getNy()
    );
    EXPECT_NEAR(F[0], 0.0, 1e-10); 
    EXPECT_NE  (F[1], 0.0);        // force non nulle en Y (LJ + gravité)
}

// ── Tests gravité ──────────────────────────────────────

TEST(ForcesTest, GraviteDirection) {
    Particle p(Vector(5.0, 5.0), Vector(0,0),
               2.0, 0, Vector(0,0), "rect");
    Vector Fg = computeGravity(p, -12.0);
    EXPECT_NEAR(Fg[0],  0.0,   1e-10);
    EXPECT_NEAR(Fg[1], -24.0,  1e-10); // m * G = 2 * (-12)
}

TEST(ForcesTest, GraviteProportionnelleMasse) {
    Particle p1(Vector(5,5), Vector(0,0), 1.0, 0, Vector(0,0), "rect");
    Particle p2(Vector(5,5), Vector(0,0), 3.0, 1, Vector(0,0), "rect");
    Vector F1 = computeGravity(p1, -12.0);
    Vector F2 = computeGravity(p2, -12.0);
    EXPECT_NEAR(F2[1], 3.0 * F1[1], 1e-10);
}

TEST(ForcesTest, GraviteNulleAvecG0) {
    Particle p(Vector(5,5), Vector(0,0), 1.0, 0, Vector(0,0), "rect");
    Vector Fg = computeGravity(p, 0.0);
    EXPECT_NEAR(Fg[0], 0.0, 1e-10);
    EXPECT_NEAR(Fg[1], 0.0, 1e-10);
}

TEST(ForcesTest, GraviteComposanteXNulle) {
    Particle p(Vector(5,5), Vector(0,0), 2.0, 0, Vector(0,0), "rect");
    Vector Fg = computeGravity(p, -12.0);
    EXPECT_NEAR(Fg[0], 0.0, 1e-10);
}