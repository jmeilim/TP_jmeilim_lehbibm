#include "../include/Forces.hxx"
#include "../include/Vector.hxx"
#include <cmath>
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

Vector forceReflexivePotentiel(const Particle& p,
                                double Lx, double Ly,
                                double epsilon, double sigma) {
    Vector F(0,0,0);
    double rcut = pow(2.0, 1.0/6.0) * sigma;
    double x = p.getPosition()[0];
    double y = p.getPosition()[1];
    double distances[4] = {x, Lx - x, y, Ly - y};
    int signes[4] = {1, -1, 1, -1};
    int composantes[4] = {0, 0, 1, 1};

    for (int k = 0; k < 4; k++) {
        double r = distances[k];
        if (r <= 0 || r >= rcut) continue;
        double sr  = sigma / (2.0 * r);
        double sr6 = sr * sr * sr * sr * sr * sr;
        double f   = -24.0 * epsilon * (1.0 / (2.0 * r)) * sr6 * (1.0 - 2.0 * sr6);
        F[composantes[k]] += signes[k] * f;
    }

    return F;
}



// bool conditionLimites(Particle& p, double Lx, double Ly, BoundaryType type) {

//     Vector& pos = p.getPosition();
//     Vector& vel = p.getVitesse();
//     double x = pos.getX();
//     double y = pos.getY();
//     if (type == REFLEXION) {
//         if (x < 0) {
//             pos.setX(-x);
//             vel.setX(-vel.getX());
//         }
//         if (x > Lx) {
//             pos.setX(2 * Lx - x);
//             vel.setX(-vel.getX());
//         }

//         if (y < 0) {
//             pos.setY(-y);
//             vel.setY(-vel.getY());
//         }
//         if (y > Ly) {
//             pos.setY(2 * Ly - y);
//             vel.setY(-vel.getY());
//         }

//         return true;
//     }

//     else if (type == ABSORPTION) {

//     if (x < 0 || x > Lx || y < 0 || y > Ly) {
//         p.setAlive(false);
//         return false;
//     }
//     }
//     else if (type == PERIODIQUE) {
//         if (x < 0) pos.setX(x + Lx);
//         if (x > Lx) pos.setX(x - Lx);
//         if (y < 0) pos.setY(y + Ly);
//         if (y > Ly) pos.setY(y - Ly);
//         return true;
//     }

//     return true;
// }


double U(double r, double eps = 1, double sig = 1){
    return 4 * eps * pow(sig/r,6) *( pow(sig/r,6)-1);
}