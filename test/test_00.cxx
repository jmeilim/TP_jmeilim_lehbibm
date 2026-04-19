#include <string> 
#include <iostream>
#include <chrono>
#include "../include/Lab3.hxx"
#include "../include/Lab2.hxx"
#include "../src/Lab3.cxx"
#include <gtest/gtest.h>




int main() {
    auto start = std::chrono::steady_clock::now();

    std::vector<Particle> particles = {
        Particle(Vector(0,0,0), Vector(0,0,0), 1, 0, Vector(0,0,0), "Soleil"),
        Particle(Vector(0,1,0), Vector(-1,0,0), 3.0e-6, 1, Vector(0,0,0), "Terre"),
        Particle(Vector(0,5.36,0), Vector(-0.425,0,0), 9.55e-4, 2, Vector(0,0,0), "Jupiter"),
        Particle(Vector(34.75,0,0), Vector(0,0.0296,0), 1.0e-14, 3, Vector(0,0,0), "Halley")
    };

    std::vector<Vector> Fo(particles.size(), Vector(1.0e-14,1.0e-14,1.0e-14));

  
    double rc = 2.5;
    double cellSize = rc;
    int nx = 10;
    int ny = 10;

    std::vector<Cellule> grid(nx * ny);

   
    stromer(particles, Fo, grid, rc, cellSize, nx, ny);

    
    Univers u(3);
    int N = 1 << 26;  

    for (int i = 0; i < N; i++) {
        u.addParticle(
            Particle(Vector(i,i,i), Vector(1,1,1), 1.0e-14, i, Vector(0,0,0), "Uniforme")
        );
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}