
#include"../include/Stromer.hxx"
#include "../include/Forces.hxx"
#include "../include/Univers.hxx"
#include "Boundary.hxx"
#include <cmath>
/**
 * @brief Implementation du Stromer-Algorithm
 * 
 * @param particleList liste des particules 
 * @param Fo  Fo vecteur des forces précédentes
 * @param grid maillage de l'espace
 * @param rc rayon de coupure
 * @param cellSize taille des cellules du maillage
 * @param nx nombre de cellules en x
 * @param ny nombre de cellules en y
 * 
 */

void stromer(Univers& u, std::vector<Vector>& Fo, double dt, int iter) {

    auto& ps = u.getParticles();
    int N = ps.size();

   
    for (int i = 0; i < N; i++) {

        if (!ps[i].isAlive()) continue;

        double m = ps[i].getMasse();
        if (m < 1e-12) m = 1e-12;

        ps[i].getPosition()[0] += dt * ps[i].getVitesse()[0]
                               + 0.5 * dt * dt * Fo[i][0] / m;

        ps[i].getPosition()[1] += dt * ps[i].getVitesse()[1]
                               + 0.5 * dt * dt * Fo[i][1] / m;

        // conditions limites
        conditionLimites(ps[i], u.getLx(), u.getLy());
    }


    u.updateCells();


    std::vector<Vector> F(N, Vector(0,0,0));

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

    for (int i = 0; i < N; i++) {

        if (!ps[i].isAlive()) continue;

        double m = ps[i].getMasse();
        if (m < 1e-12) m = 1e-12;

        ps[i].getVitesse()[0] += 0.5 * dt * (Fo[i][0] + F[i][0]) / m;
        ps[i].getVitesse()[1] += 0.5 * dt * (Fo[i][1] + F[i][1]) / m;
    }


    Fo = F;

    
}

