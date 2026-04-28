
#include"../include/Stromer.hxx"
#include "../include/Forces.hxx"
#include "../include/Univers.hxx"
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

void stromer(Univers& u, std::vector<Vector>& Fo, double dt) {

std::vector<Particle>& particleList = u.getParticles();
std::vector<Cellule>& grid = u.getGrid();
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

    u.updateCells();
    std::vector<Vector> F(N, Vector(0,0,0));
    for (int i = 0; i < N; i++){
        F[i] = computeForce(particleList[i], particleList, u.getRc(), u.getGrid(), u.getCellSize(), u.getNx(), u.getNy());
    }
    
    for (int i = 0; i < N; i++) {
        double m = particleList[i].getMasse();
        if (m < 1e-12) m = 1e-12;

        particleList[i].getVitesse() += (F[i] + Fo[i])*(0.5*dt/m);
    }
    Fo = F;
}


