
#include"../include/Stromer.hxx"
#include "../include/Forces.hxx"
#include "../include/Univers.hxx"
#include "../include/Boundary.hxx"
#include "../include/GenereException.hxx"
#include <cmath>


 /**
 * Implémentation de l'algorithme de Störmer-Verlet.
 *
 * Cet algorithme est choisi pour sa stabilité numérique et sa conservation
 * de l'énergie sur le long terme, ce qui est essentiel pour une simulation
 * moléculaire correcte.
 *
 * Ordre des étapes à chaque itération :
 *   1. Mise à jour des positions
 *   2. Application des conditions aux limites
 *   3. Mise à jour de la grille
 *   4. Calcul des nouvelles forces
 *   5. Mise à jour des vitesses
 *   6. Thermostat (toutes les 1000 itérations, uniquement sur "rect")
 */

void stromer(Univers& u, std::vector<Vector>& Fo, double dt, int iter) {

    auto& ps = u.getParticles();
    int N = ps.size();

    if (dt <= 0)
        throw GenereException("dt doit être > 0");

    // 1. Mise à jour des positions
    for (int i = 0; i < N; i++) {

        if (!ps[i].isAlive()) continue;


        // protection contre une masse nulle qui causerait
        // une division par zéro dans le calcul de l'accélération
        double m = ps[i].getMasse();
        if (m < 1e-12) m = 1e-12;

        ps[i].getPosition()[0] += dt * ps[i].getVitesse()[0]
                               + 0.5 * dt * dt * Fo[i][0] / m;

        ps[i].getPosition()[1] += dt * ps[i].getVitesse()[1]
                               + 0.5 * dt * dt * Fo[i][1] / m;

        // conditions limites
        conditionLimites(ps[i], u.getLx(), u.getLy());
    }

    // 2. Mise à jour de la grille après déplacement
    u.updateCells();


    std::vector<Vector> F(N, Vector(0,0,0));
    // 3. Calcul des nouvelles forces
    for (int i = 0; i < N; i++) {
        if (!ps[i].isAlive()) continue;

        F[i] = computeForce(
            ps[i],
            ps,
            u.getRc(),
            u.getGrid(),  
            u.getCellSize(),
            u.getNx(),
            u.getNy()
        );
    }
    // 4. Mise à jour des vitesses
    for (int i = 0; i < N; i++) {

        if (!ps[i].isAlive()) continue;

        double m = ps[i].getMasse();
        if (m < 1e-12) m = 1e-12;

        ps[i].getVitesse()[0] += 0.5 * dt * (Fo[i][0] + F[i][0]) / m;
        ps[i].getVitesse()[1] += 0.5 * dt * (Fo[i][1] + F[i][1]) / m;
    }

    // 5. Les nouvelles forces deviennent les anciennes pour l'itération suivante
    Fo = F;


    // 6. Thermostat : limite la divergence de l'énergie cinétique
    // On rescale les vitesses des "rect" toutes les 1000 itérations
    // avec beta = sqrt(Ec_target / Ec) pour rester proche de l'énergie cible
    if (iter % 1000 == 0) {
        double Ec = 0.0;
        int N_rect = 0;

        for (const auto& p : ps) {
            if (!p.isAlive()) continue;
            if (p.getCat() != "rect") continue;
            double vx = p.getVitesse()[0];
            double vy = p.getVitesse()[1];
            Ec += 0.5 * p.getMasse() * (vx*vx + vy*vy);
            N_rect++;
        }

        if (N_rect == 0)
            throw GenereException("Aucune particule rect pour le thermostat");
    
        if (Ec < 1e-12)
            throw GenereException("Energie cinétique nulle, beta impossible");

        double Ec_target = 0.005 * N_rect;

        if (Ec > 1e-12) {
            double beta = std::sqrt(Ec_target / Ec);
     
            for (auto& p : ps) {
                if (!p.isAlive()) continue;
                if (p.getCat() != "rect") continue;
                p.getVitesse()[0] *= beta;
                p.getVitesse()[1] *= beta;
            }
  
        }
    }
}

