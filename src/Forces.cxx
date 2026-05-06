#include "../include/Forces.hxx"
#include "../include/Vector.hxx"
#include "../include/Univers.hxx"
#include "../include/Particle.hxx"
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

                if (!ps[k].isAlive()) continue;
                if (ps[k].getId() == p.getId()) continue;

                double dx = ps[k].getPosition()[0] - p.getPosition()[0];
                double dy = ps[k].getPosition()[1] - p.getPosition()[1];

                double r2 = dx*dx + dy*dy;

                if (r2 > rc*rc) continue;
                if (r2 < 0.25) r2 = 0.25;

                double r = sqrt(r2);

                double sr = 1.0 / r;
                double sr2 = sr * sr;
                double sr6 = sr2 * sr2 * sr2;

                double f = 24.0 * (1.0 / r2) * sr6 * (1.0 - 2.0 * sr6);

                F[0] += f * dx;
                F[1] += f * dy;
            }
        }    }
    if (p.getCat() == "rect") {
    
    F += forceMurBas(p, 1, 1);
    }
    F += computeGravity(p, -12);


    return F;
}
Vector computeGravity(const Particle& p, double G) {
    return Vector(0.0, p.getMasse() * G);
}
Vector forceMurBas(const Particle& p, double epsilon, double sigma) {
    Vector F(0,0,0);
    double y = p.getPosition()[1];
    double rcut = pow(2.0, 1.0/6.0) * sigma;


    if (y <= 0) y = 1e-3 * sigma;
    if (y >= rcut) return F;

    double sr  = sigma / (2.0 * y);
    double sr6 = sr*sr*sr*sr*sr*sr;
    double f   = -24.0 * epsilon * (1.0 / (2.0 * y)) * sr6 * (1.0 - 2.0 * sr6);
    F[1] += f;
    return F;
}



double U(double r, double eps = 1, double sig = 1){
    return 4 * eps * pow(sig/r,6) *( pow(sig/r,6)-1);
}