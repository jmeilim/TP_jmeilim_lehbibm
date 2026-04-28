#pragma once

#include <vector>
#include <string>
#include "Particle.hxx"

struct Cellule {
    Vector center;
    std::vector<int> particles;
    Cellule() : center(0.0, 0.0, 0.0) {}
};

void updateCells(std::vector<Cellule>& grid, std::vector<Particle>& particles,double cellSize,int nx,int ny);