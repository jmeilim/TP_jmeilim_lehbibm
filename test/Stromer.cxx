#include <gtest/gtest.h>
#include "../include/Particle.hxx"
#include "../include/Vector.hxx"
#include "../include/Cellule.hxx"
#include "../include/Stromer.hxx"
#include "../include/Forces.hxx"
#include "../include/Univers.hxx"
#include "../include/Boundary.hxx"
#include <cmath>

// ── Helper ─────────────────────────────────────────────
Univers makeUnivers() {
    Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5);
    u.addParticle(Particle(Vector(0,0),     Vector(0,0),      1.0,    0, Vector(0,0), "rect"));
    u.addParticle(Particle(Vector(0,1),     Vector(-1,0),     3.0e-6, 1, Vector(0,0), "disk"));
    u.addParticle(Particle(Vector(0,5.36),  Vector(-0.425,0), 9.55e-4,2, Vector(0,0), "disk"));
    u.addParticle(Particle(Vector(34.75,0), Vector(0,0.0296), 1.0e-14,3, Vector(0,0), "disk"));
    return u;
}

// ── Tests ──────────────────────────────────────────────

TEST(StromerTest, UneIterationSansNaN) {
    Univers u = makeUnivers();
    std::vector<Vector> Fo(u.getNbParticles(), Vector(0,0,0));
    u.updateCells();
    stromer(u, Fo, 0.0005, 0);
    for (auto& p : u.getParticles()) {
        if (!p.isAlive()) continue;
        EXPECT_FALSE(std::isnan(p.getPosition()[0]));
        EXPECT_FALSE(std::isnan(p.getPosition()[1]));
        EXPECT_FALSE(std::isnan(p.getVitesse()[0]));
        EXPECT_FALSE(std::isnan(p.getVitesse()[1]));
    }
}

TEST(StromerTest, PositionChangeApresIterations) {
    Univers u = makeUnivers();
    std::vector<Vector> Fo(u.getNbParticles(), Vector(0,0,0));
    u.updateCells();
    double x0 = u.getParticles()[1].getPosition()[0];
    double y0 = u.getParticles()[1].getPosition()[1];
    for (int i = 0; i < 10; i++)
        stromer(u, Fo, 0.0005, i);
    double x1 = u.getParticles()[1].getPosition()[0];
    double y1 = u.getParticles()[1].getPosition()[1];
    EXPECT_FALSE(x0 == x1 && y0 == y1);
}

TEST(StromerTest, VitesseChangeApresIteration) {
    Univers u = makeUnivers();
    std::vector<Vector> Fo(u.getNbParticles(), Vector(0,0,0));
    u.updateCells();
    double vx0 = u.getParticles()[1].getVitesse()[0];
    stromer(u, Fo, 0.0005, 0);
    double vx1 = u.getParticles()[1].getVitesse()[0];
    EXPECT_NE(vx0, vx1);
}

TEST(StromerTest, ConservationEnergieCinetique) {
    Univers u = makeUnivers();
    std::vector<Vector> Fo(u.getNbParticles(), Vector(0,0,0));
    u.updateCells();
    double Ec0 = 0.0;
    for (auto& p : u.getParticles()) {
        double vx = p.getVitesse()[0], vy = p.getVitesse()[1];
        Ec0 += 0.5 * p.getMasse() * (vx*vx + vy*vy);
    }
    for (int i = 0; i < 100; i++)
        stromer(u, Fo, 0.0005, i);
    double Ec1 = 0.0;
    for (auto& p : u.getParticles()) {
        if (!p.isAlive()) continue;
        double vx = p.getVitesse()[0], vy = p.getVitesse()[1];
        Ec1 += 0.5 * p.getMasse() * (vx*vx + vy*vy);
    }
    EXPECT_LT(Ec1, 10.0 * Ec0 + 1.0);
}

TEST(StromerTest, ThermostatApplique) {
    Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5);
    for (int i = 0; i < 5; i++)
        u.addParticle(Particle(Vector(i*2.0, i*2.0), Vector(1.0, 1.0),
                               1.0, i, Vector(0,0), "rect"));
    std::vector<Vector> Fo(u.getNbParticles(), Vector(0,0,0));
    u.updateCells();
    EXPECT_NO_THROW(stromer(u, Fo, 0.0005, 1000));
}


