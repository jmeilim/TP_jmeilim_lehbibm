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
 */

void stromer(std::vector<Particle>& particleList,
             std::vector<Vector>& Fo,
             std::vector<Cellule>& grid,
             double rc,
             double cellSize,
             int nx,
             int ny) {

    double dt = 0.001;
    int N = particleList.size();

    std::vector<Vector> F(N, Vector(0.0,0.0,0.0));

    updateCells(grid, particleList, cellSize, nx, ny);

    for (int i = 0; i < N; i++)
        F[i] = computeForce(particleList[i], particleList, rc, grid, cellSize, nx, ny);

    double t = 0;

    

    for (int i = 0; i < N; i++) {
        double m = particleList[i].getMasse();
        if (m < 1e-12) m = 1e-12;

        for (int d = 0; d < 2; d++) {
            particleList[i].getPosition()[d] +=
                dt * particleList[i].getVitesse()[d]
                + 0.5 * dt * dt * F[i][d] / m;
        }
    }

    for (int i = 0; i < N; i++)
        Fo[i] = F[i];
    updateCells(grid, particleList, cellSize, nx, ny);

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
    
}

/**
 * @brief Calcule la force gravitationnelle sur une particule
 * 
 * @param p particule cible
 * @param ps liste des particules
 * @return Vector force résultante
 */
Vector computeForce(const Particle& p,
                    std::vector<Particle>& ps,
                    double rc,
                    std::vector<Cellule>& grid,
                    double cellSize,
                    int nx,
                    int ny) {

    Vector F(0.0, 0.0, 0.0);

    int px = p.getPosition()[0] / cellSize;
    int py = p.getPosition()[1] / cellSize;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {

            int vx = px + i;
            int vy = py + j;

            if (vx < 0 || vy < 0 || vx >= nx || vy >= ny) continue;

            int id = vx * ny + vy;

            double dx = grid[id].center[0] - p.getPosition()[0];
            double dy = grid[id].center[1] - p.getPosition()[1];

            double r2 = dx*dx + dy*dy;
            if (r2 > rc*rc) continue;

            for (int k : grid[id].particles) {

                if (ps[k].getId() == p.getId()) continue;

                double dxp = ps[k].getPosition()[0] - p.getPosition()[0];
                double dyp = ps[k].getPosition()[1] - p.getPosition()[1];

                double r2p = dxp*dxp + dyp*dyp;
                if (r2p < 1e-6) continue;

                double r = sqrt(r2p);
                if (r > rc) continue;
                double sr = 1.0 / r;
                double sr2 = sr * sr;
                double sr6 = sr2 * sr2 * sr2;

                double f = 24.0 * sr6 * (1.0 - 2.0 * sr6) / r2p;
                F[0] += f * dxp;
                F[1] += f * dyp;
            }
        }
    }

    return F;
}
