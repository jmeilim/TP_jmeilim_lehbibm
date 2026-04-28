
#include"../include/Stromer.hxx"
#include "../include/Forces.hxx"
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


void updateCells(std::vector<Cellule>& grid, std::vector<Particle>& particles,double cellSize,int nx,int ny) {

    for (auto& c : grid)
        c.particles.clear();

    for (int i = 0; i < (int )particles.size(); i++) {

        int cx = particles[i].getPosition()[0] / cellSize;
        int cy = particles[i].getPosition()[1] / cellSize;

        if (cx < 0 || cy < 0 || cx >= nx || cy >= ny) continue;

        int id = cx * ny + cy;
        grid[id].particles.push_back(i);
    }
}