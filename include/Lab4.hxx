#pragma once

#include <vector>
#include "Lab2.hxx"
#include "Lab3.hxx"



void updateCells(std::vector<Cellule>& grid,
                 std::vector<Particle>& particles,
                 double cellSize,
                 int nx,
                 int ny);