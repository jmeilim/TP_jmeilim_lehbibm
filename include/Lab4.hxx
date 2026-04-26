#pragma once

#include <vector>
#include "Lab2.hxx"
#include <cmath>
#include "Lab3.hxx"

/**
 * @brief Potentiel de Lennard-Jones
 */
inline double U(double r, double eps = 1, double sig = 1){
    return 4 * eps * pow(sig/r,6) *( pow(sig/r,6)-1);
}
void updateCells(std::vector<Cellule>& grid, std::vector<Particle>& particles,double cellSize,int nx,int ny);