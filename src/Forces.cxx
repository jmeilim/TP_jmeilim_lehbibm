#include "../include/Forces.hxx"
#include "../include/Vector.hxx"
#include "../include/Univers.hxx"
#include "../include/Particle.hxx"
#include <cmath>
/**
 * Calcule la force totale sur une particule :
 *   - interactions de Lennard-Jones avec les voisines (dans rc)
 *   - potentiel de paroi basse pour les particules "rect"
 *   - gravité uniforme sur toutes les particules
 *
 * On ne parcourt que les 9 cellules voisines grâce à la grille,
 * ce qui évite de comparer la particule avec toutes les autres.
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



                // évite la division par zéro si deux particules
                // se superposent exactement suite à une perturbation numérique
                
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
    
    // potentiel de paroi LJ — empêche les particules "rect" de traverser le sol
    if (p.getCat() == "rect") {
    
    F += forceMurBas(p, 1, 1);
    }
    F += computeGravity(p, -12);


    return F;
}



/**
 * Potentiel LJ de paroi basse.
 * Modélise un mur réflexif via un potentiel répulsif
 * actif uniquement sous rcut = 2^(1/6)*sigma.
 */

Vector computeGravity(const Particle& p, double G) {
    return Vector(0.0, p.getMasse() * G);
}
Vector forceMurBas(const Particle& p, double epsilon, double sigma) {
    Vector F(0,0,0);
    double y = p.getPosition()[1];
    double rcut = pow(2.0, 1.0/6.0) * sigma;


    // si la particule est exactement sur le mur, on évite la singularité
    // en la plaçant à une très petite distance
    if (y <= 0) y = 1e-3 * sigma;


    // au-delà de rcut, le potentiel LJ de paroi est négligeable
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