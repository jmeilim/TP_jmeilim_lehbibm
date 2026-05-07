#include "../include/Boundary.hxx"
#include <cmath>


// Réflexion sur les 4 bords :
// la particule rebondit symétriquement, sa vitesse est inversée


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




// Absorption sur les 4 bords :
// la particule est désactivée dès qu'elle sort du domaine

void absorption(Particle& p, double Lx, double Ly) {
    Vector& pos = p.getPosition();
    if (pos.getX() < 0  || pos.getX() > Lx ||
        pos.getY() < 0  || pos.getY() > Ly)
        p.setAlive(false);
}



// Périodique sur les 4 bords :
// la particule réapparaît du côté opposé sans changer de vitesse


void periodique(Particle& p, double Lx, double Ly) {
    Vector& pos = p.getPosition();

    if (pos.getX() < 0)  pos.setX(pos.getX() + Lx);
    if (pos.getX() > Lx) pos.setX(pos.getX() - Lx);
    if (pos.getY() < 0)  pos.setY(pos.getY() + Ly);
    if (pos.getY() > Ly) pos.setY(pos.getY() - Ly);
}

/**
 * Condition aux limites utilisée dans la simulation de collision :
 *   - gauche/droite : réflexion
 *   - bas           : réflexion (complétée par le potentiel de paroi LJ)
 *   - haut          : absorption — les particules qui sortent par le haut
 *                     sont définitivement retirées de la simulation
 */

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

    // on place la particule à 1e-3 plutôt que 0 pour éviter que
    // forceMurBas ne voie y=0, ce qui causerait une division par zéro
    if (pos.getY() < 0) {
        pos.setY(1e-3);
        vel.setY(std::abs(vel.getY()));
    }
    return true;
}