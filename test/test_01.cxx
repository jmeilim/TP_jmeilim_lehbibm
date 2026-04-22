
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "../include/Lab2.hxx"
#include "../include/Lab4.hxx"
#include <gtest/gtest.h>


int main() {

    std::ofstream file("lab.dat");
    double rm = 0.3;
    double rmm = 3.0;
    int N = 500;

    for (int i = 0; i < N; i++) {
        double r = rm + (rmm - rm) * i / (N - 1);
        double res = U(r);
        file << r << " " << res << std::endl;
    }

    int nx = 20, ny = 20;
    double L = 50.0;
    double cellSize = L / nx;

    std::vector<Particle> particles;

    particles.push_back(Particle(Vector(0,0,0), Vector(0,0,0), 1, 0, Vector(0,0,0), "sun"));
    particles.push_back(Particle(Vector(0,1,0), Vector(-1,0,0), 3e-6, 1, Vector(0,0,0), "earth"));
    particles.push_back(Particle(Vector(0,5.36,0), Vector(-0.425,0,0), 9.55e-4, 2, Vector(0,0,0), "jupiter"));
    particles.push_back(Particle(Vector(34.75,0,0), Vector(0,0.0296,0), 1e-14, 3, Vector(0,0,0), "halley"));

    std::vector<Cellule> grid(nx * ny);

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            int id = i * ny + j;
            grid[id].center = Vector(
                (i + 0.5) * cellSize,
                (j + 0.5) * cellSize,
                0
            );
        }
    }

    updateCells(grid, particles, cellSize, nx, ny);

    return 0;
}