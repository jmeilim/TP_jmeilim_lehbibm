#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "../include/Lab2.hxx"
#include "../include/Lab4.hxx"



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

    for (int i = 0; i < (int )particles.size(); i++) {

        int cx = particles[i].getPosition()[0] / cellSize;
        int cy = particles[i].getPosition()[1] / cellSize;

        if (cx < 0 || cy < 0 || cx >= nx || cy >= ny) continue;

        int id = cx * ny + cy;
        grid[id].particles.push_back(i);
    }
}


