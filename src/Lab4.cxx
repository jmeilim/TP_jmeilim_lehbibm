#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "../include/Lab2.hxx"
#include "../include/Lab4.hxx"




/**
 * @brief Potentiel de Lennard-Jones
 */
double U(double r, double eps = 1, double sig = 1){
    return 4 * eps * pow(sig/r,6) *( pow(sig/r,6)-1);
}

// Construction de maillage 

/**
 * @brief claase pour representer l'univers de simulation
 */
class Univers {
public:
    double eps;   ///< profondeur du potentiel
    double sig;  ///< distance caractéristique
    int  dim;     ///< dimension 
    double ld;    ///< taille de la boîte
    double rc;   ///< rayon de coupure
    std::vector< Cellule* > cellules ; 
    
    Univers(double e, double s, int dimension, double l, double rcut,std::vector< Cellule* > cellules )
        : eps(e), sig(s), dim(dimension), ld(l), rc(rcut) , cellules(cellules) {}

    
};

void updateCells(std::vector<Cellule>& grid, std::vector<Particle>& particles,double cellSize,int nx,int ny) {

    for (auto& c : grid)
        c.particles.clear();

    for (int i = 0; i < particles.size(); i++) {

        int cx = particles[i].getPosition()[0] / cellSize;
        int cy = particles[i].getPosition()[1] / cellSize;

        if (cx < 0 || cy < 0 || cx >= nx || cy >= ny) continue;

        int id = cx * ny + cy;
        grid[id].particles.push_back(i);
    }
}


// int main() {

//     std::ofstream file("lab.dat");
//     double rm = 0.3;
//     double rmm = 3.0;
//     int N = 500;

//     for (int i = 0; i < N; i++) {
//         double r = rm + (rmm - rm) * i / (N - 1);
//         double res = U(r);
//         file << r << " " << res << std::endl;
//     }

//     int nx = 20, ny = 20;
//     double L = 50.0;
//     double cellSize = L / nx;

//     std::vector<Particle> particles;

//     particles.push_back(Particle(Vector(0,0,0), Vector(0,0,0), 1, 0, Vector(0,0,0), "sun"));
//     particles.push_back(Particle(Vector(0,1,0), Vector(-1,0,0), 3e-6, 1, Vector(0,0,0), "earth"));
//     particles.push_back(Particle(Vector(0,5.36,0), Vector(-0.425,0,0), 9.55e-4, 2, Vector(0,0,0), "jupiter"));
//     particles.push_back(Particle(Vector(34.75,0,0), Vector(0,0.0296,0), 1e-14, 3, Vector(0,0,0), "halley"));

//     std::vector<Cellule> grid(nx * ny);

//     for (int i = 0; i < nx; i++) {
//         for (int j = 0; j < ny; j++) {
//             int id = i * ny + j;
//             grid[id].center = Vector(
//                 (i + 0.5) * cellSize,
//                 (j + 0.5) * cellSize,
//                 0
//             );
//         }
//     }

//     updateCells(grid, particles, cellSize, nx, ny);

//     return 0;
// }