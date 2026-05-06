#include "../include/Particle.hxx"
#include "../include/Boundary.hxx"
#include "../include/Vector.hxx"
#include <gtest/gtest.h>

TEST(BoundaryTest, AbsorptionTop) {
    Particle p(Vector(5.0, 11.0), Vector(0.0, 0.0),
               1.0, 0, Vector(0.0, 0.0), "A");

    // ton API actuelle
    conditionLimites(p, 10.0, 10.0);

    EXPECT_FALSE(p.isAlive());
}
