#include <gtest/gtest.h>
#include "../include/Particle.hxx"
#include "../include/Vector.hxx"
#include "../include/Univers.hxx"
#include "../include/Stromer.hxx"
#include "../include/GenereException.hxx"

// ── Tests Univers ──────────────────────────────────────

TEST(GenereExceptionTest, UniversRcNegatif) {
    EXPECT_THROW(
        Univers u(1.0, 1.0, 2, 250.0, 180.0, -1.0),
        GenereException
    );
}

TEST(GenereExceptionTest, UniversRcNul) {
    EXPECT_THROW(
        Univers u(1.0, 1.0, 2, 250.0, 180.0, 0.0),
        GenereException
    );
}

TEST(GenereExceptionTest, UniversLxNul) {
    EXPECT_THROW(
        Univers u(1.0, 1.0, 2, 0.0, 180.0, 2.5),
        GenereException
    );
}

TEST(GenereExceptionTest, UniversLyNegatif) {
    EXPECT_THROW(
        Univers u(1.0, 1.0, 2, 250.0, -1.0, 2.5),
        GenereException
    );
}

TEST(GenereExceptionTest, UniversValide) {
    EXPECT_NO_THROW(
        Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5)
    );
}

// ── Tests Stromer ──────────────────────────────────────

TEST(GenereExceptionTest, StromerDtNegatif) {
    Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5);
    u.addParticle(Particle(Vector(5.0, 5.0), Vector(0,0),
                           1.0, 0, Vector(0,0), "rect"));
    std::vector<Vector> Fo(1, Vector(0,0,0));
    u.updateCells();
    EXPECT_THROW(
        stromer(u, Fo, -0.001, 0),
        GenereException
    );
}

TEST(GenereExceptionTest, StromerDtNul) {
    Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5);
    u.addParticle(Particle(Vector(5.0, 5.0), Vector(0,0),
                           1.0, 0, Vector(0,0), "rect"));
    std::vector<Vector> Fo(1, Vector(0,0,0));
    u.updateCells();
    EXPECT_THROW(
        stromer(u, Fo, 0.0, 0),
        GenereException
    );
}

TEST(GenereExceptionTest, StromerDtValide) {
    Univers u(1.0, 1.0, 2, 250.0, 180.0, 2.5);
    u.addParticle(Particle(Vector(5.0, 5.0), Vector(0,0),
                           1.0, 0, Vector(0,0), "rect"));
    std::vector<Vector> Fo(1, Vector(0,0,0));
    u.updateCells();
    EXPECT_NO_THROW(
        stromer(u, Fo, 0.0005, 0)
    );
}

// ── Test message d'erreur ──────────────────────────────

TEST(GenereExceptionTest, MessageContientPrefixe) {
    try {
        Univers u(1.0, 1.0, 2, 250.0, 180.0, -1.0);
        FAIL() << "Exception attendue non levée";
    } catch (const GenereException& e) {
        std::string msg(e.what());
        EXPECT_NE(msg.find("[Erreur]"), std::string::npos);
    }
}

TEST(GenereExceptionTest, ExceptionHeriteDeSdtException) {
    // GenereException doit être attrapable comme std::exception
    try {
        throw GenereException("test");
        FAIL() << "Exception attendue non levée";
    } catch (const std::exception& e) {
        SUCCEED();
    }
}