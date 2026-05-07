#include "../include/Boundary.hxx"
#include <cmath>

// ── Réflexion sur les 4 bords ──────────────────────────
void reflexion(Particle& p, double Lx, double Ly) {
    Vector& pos = p.getPosition();
    Vector& vel = p.getVitesse();

    if (pos.getX() < 0) {
        pos.setX(-pos.getX());
        vel.setX(std::abs(vel.getX()));
    }
    if (pos.getX() > Lx) {
        pos.setX(2*Lx - pos.getX());
        vel.setX(-std::abs(vel.getX()));
    }
    if (pos.getY() < 0) {
        pos.setY(-pos.getY());
        vel.setY(std::abs(vel.getY()));
    }
    if (pos.getY() > Ly) {
        pos.setY(2*Ly - pos.getY());
        vel.setY(-std::abs(vel.getY()));
    }
}

// ── Absorption sur les 4 bords ─────────────────────────
void absorption(Particle& p, double Lx, double Ly) {
    Vector& pos = p.getPosition();
    if (pos.getX() < 0  || pos.getX() > Lx ||
        pos.getY() < 0  || pos.getY() > Ly) {
        p.setAlive(false);
    }
}

// ── Périodique sur les 4 bords ─────────────────────────
void periodique(Particle& p, double Lx, double Ly) {
    Vector& pos = p.getPosition();

    if (pos.getX() < 0)   pos.setX(pos.getX() + Lx);
    if (pos.getX() > Lx)  pos.setX(pos.getX() - Lx);
    if (pos.getY() < 0)   pos.setY(pos.getY() + Ly);
    if (pos.getY() > Ly)  pos.setY(pos.getY() - Ly);
}

bool conditionLimites(Particle& p, double Lx, double Ly) {
    Vector& pos = p.getPosition();
    Vector& vel = p.getVitesse();

    if (pos.getX() < 0) {
        pos.setX(-pos.getX());
        vel.setX(std::abs(vel.getX()));
    }
    if (pos.getX() > Lx) {
        pos.setX(2*Lx - pos.getX());
        vel.setX(-std::abs(vel.getX()));
    }
    if (pos.getY() > Ly) {
        p.setAlive(false);
        return false;
    }
    if (pos.getY() < 0) {
        pos.setY(1e-3);
        vel.setY(std::abs(vel.getY()));
    }
    return true;
}