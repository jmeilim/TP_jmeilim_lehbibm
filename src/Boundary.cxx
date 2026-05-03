#include "Boundary.hxx"
#include <cmath>

bool conditionLimites(Particle& p, double Lx, double Ly) {

    Vector& pos = p.getPosition();
    Vector& vel = p.getVitesse();

    double x = pos.getX();
    double y = pos.getY();
    if (x < 0)  pos.setX(x + Lx);
    if (x > Lx) pos.setX(x - Lx);

    if (y > Ly) {
        p.setAlive(false);
        return false;
    }
    if (y < 0) {
        pos.setY(1e-3);
        vel.setY(std::abs(vel.getY())); // on s'assure qu'elle remonte
    }
    return true;
}