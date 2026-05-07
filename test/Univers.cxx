#include <gtest/gtest.h>
#include "../include/Particle.hxx"
#include "../include/Vector.hxx"
#include "../include/Cellule.hxx"
#include "../include/Univers.hxx"

TEST(UniversTest, ConstructeurValide) {
    Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5);
    EXPECT_DOUBLE_EQ(u.getEps(),  1.0);
    EXPECT_DOUBLE_EQ(u.getSig(),  1.0);
    EXPECT_DOUBLE_EQ(u.getLx(),   250.0);
    EXPECT_DOUBLE_EQ(u.getLy(),   180.0);
    EXPECT_DOUBLE_EQ(u.getRc(),   2.5);
    EXPECT_EQ(u.getNbParticles(), 0);
}

TEST(UniversTest, GrilleInitialisee) {
    Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5);
    EXPECT_EQ(u.getNx(), (int)(250.0 / 2.5));
    EXPECT_EQ(u.getNy(), (int)(180.0 / 2.5));
    EXPECT_EQ((int)u.getGrid().size(), u.getNx() * u.getNy());
}

TEST(UniversTest, AddParticle) {
    Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5);
    u.addParticle(Particle(Vector(1.0, 1.0), Vector(0.0, 0.0),
                           1.0, 0, Vector(0.0, 0.0), "rect"));
    EXPECT_EQ(u.getNbParticles(), 1);
}

TEST(UniversTest, AddMultipleParticles) {
    Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5);
    for (int i = 0; i < 10; i++)
        u.addParticle(Particle(Vector(i*2.0, i*2.0), Vector(0,0),
                               1.0, i, Vector(0,0), "rect"));
    EXPECT_EQ(u.getNbParticles(), 10);
}

TEST(UniversTest, UpdateCellsRempliGrille) {
    Univers u(1.0, 1.0, 2, 10.0, 10.0, 2.5);
    u.addParticle(Particle(Vector(1.0, 1.0), Vector(0.0, 0.0),
                           1.0, 0, Vector(0.0, 0.0), "rect"));
    u.updateCells();
    bool found = false;
    for (auto& c : u.getGrid())
        if (!c.particles.empty()) { found = true; break; }
    EXPECT_TRUE(found);
}

TEST(UniversTest, CellSizeEgalRc) {
    Univers u(1.0, 1.0, 2, 10.0, 10.0, 2.5);
    EXPECT_DOUBLE_EQ(u.getCellSize(), 2.5);
}

TEST(UniversTest, ParticuleHorsDomaine) {
    
    Univers u(1.0, 1.0, 2, 10.0, 10.0, 2.5);
    u.addParticle(Particle(Vector(50.0, 50.0), Vector(0,0),
                           1.0, 0, Vector(0,0), "rect"));
    u.updateCells();
    bool found = false;
    for (auto& c : u.getGrid())
        if (!c.particles.empty()) { found = true; break; }
    EXPECT_FALSE(found);
}