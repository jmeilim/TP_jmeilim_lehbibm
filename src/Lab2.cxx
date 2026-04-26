#include <string> 
#include <random>
#include <iostream>
#include <chrono>
#include "../include/Lab3.hxx"
#include "../include/Lab2.hxx"
#include "../include/Lab4.hxx"

Vector computeForce(const Particle& p,
                    std::vector<Particle>& ps,
                    double rc,
                    std::vector<Cellule>& grid,
                    double cellSize,
                    int nx,
                    int ny);


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

void stromer(std::vector<Particle>& particleList,std::vector<Vector>& Fo,std::vector<Cellule>& grid,double rc,double cellSize,int nx,int ny,double dt) {

    int N = particleList.size();

    for (int i = 0; i < N; i++) {
        double m = particleList[i].getMasse();
        if (m < 1e-12) m = 1e-12;

        for (int d = 0; d < 2; d++) {
            particleList[i].getPosition()[d] +=
                dt * particleList[i].getVitesse()[d]
                + 0.5 * dt * dt * Fo[i][d] / m;
        }
    }

    updateCells(grid, particleList, cellSize, nx, ny);
    std::vector<Vector> F(N, Vector(0,0,0));
    for (int i = 0; i < N; i++)
        F[i] = computeForce(particleList[i], particleList, rc, grid, cellSize, nx, ny);

    for (int i = 0; i < N; i++) {
        double m = particleList[i].getMasse();
        if (m < 1e-12) m = 1e-12;

        for (int d = 0; d < 2; d++) {
            particleList[i].getVitesse()[d] +=
                0.5 * dt * (F[i][d] + Fo[i][d]) / m;
        }
    }
    Fo = F;
}

/**
 * @brief Calcule la force gravitationnelle sur une particule
 * 
 * @param p particule cible
 * @param ps liste des particules
 * @param rc rayon de coupure
 * @param grid maillage de l'espace
 * @param cellSize taille des cellules du maillage
 * @param nx nombre de cellules en x
 * @param ny nombre de cellules en y
 * @return Vector force résultante
 * 
 */
Vector computeForce(const Particle& p,std::vector<Particle>& ps,double rc,std::vector<Cellule>& grid,double cellSize,int nx,int ny) {

    Vector F(0.0, 0.0, 0.0);

    int px = (int)(p.getPosition()[0] / cellSize);
    int py = (int)(p.getPosition()[1] / cellSize);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int vx = px + i;
            int vy = py + j;
            
            if (vx < 0 || vy < 0 || vx >= nx || vy >= ny) continue;
            int id = vx * ny + vy;

            for (int k : grid[id].particles) {
                if (ps[k].getId() == p.getId()) continue;

                double dxp = ps[k].getPosition()[0] - p.getPosition()[0];
                double dyp = ps[k].getPosition()[1] - p.getPosition()[1];
                double r2p = dxp*dxp + dyp*dyp;


                if (r2p < 1e-6) continue;
                double r = sqrt(r2p);
                if (r > rc) continue;

      
                double sr  = 1 / r;
                double sr2 = sr * sr;
                double sr6 = sr2 * sr2 * sr2;


                double f = 24.0 * 5 / r2p * sr6 * (1.0 - 2.0 * sr6);

                F[0] += f * dxp;
                F[1] += f * dyp;
            }
        }
    }

    return F;
}
