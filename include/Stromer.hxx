#pragma once
#include <vector>
#include "Particle.hxx"
#include "Cellule.hxx"


void stromer(std::vector<Particle>& particleList,
             std::vector<Vector>& Fo,
             std::vector<Cellule>& grid,
             double rc,
             double cellSize,
             int nx,
             int ny,
             double dt ) ;


void updateCells( std::vector<Cellule>& grid,
            std::vector<Particle>& particles,
            double cellSize,
            int nx,
            int ny
            );