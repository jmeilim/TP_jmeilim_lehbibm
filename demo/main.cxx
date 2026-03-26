#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

#include "../include/Lab2.hxx"
#include "../include/Lab4.hxx"

int main() {

    // ===== Paramètres =====
    double sigma = 1.0;
    double d = pow(2.0, 1.0/6.0) * sigma;

    double rc = 2.5 * sigma;
    double dt = 0.001;
    double tend = 1;

    // ===== Particules =====
    std::vector<Particle> particles;

    // ===== Rectangle (bleu) =====
    for (int i = 0; i < 160; i++) {
        for (int j = 0; j < 40; j++) {

            Vector pos(i * d, j * d, 0);
            Vector vel(0, 0, 0);

            particles.push_back(
                Particle(pos, vel, 1.0, particles.size(), Vector(0,0,0), "rect")
            );
        }
    }

    // ===== Carré (rouge) =====
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {

            Vector pos(40 + i * d, 60 + j * d, 0);
            Vector vel(0, -10, 0);

            particles.push_back(
                Particle(pos, vel, 1.0, particles.size(), Vector(0,0,0), "square")
            );
        }
    }

    // ===== Grille =====
    int nx = 100, ny = 100;
    double L = 300.0;
    double cellSize = L / nx;

    std::vector<Cellule> grid(nx * ny);

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            grid[i * ny + j].center = Vector(
                (i + 0.5) * cellSize,
                (j + 0.5) * cellSize,
                0
            );
        }
    }

    // ===== Forces =====
    std::vector<Vector> Fo(particles.size(), Vector(0,0,0));

    // ===== Simulation =====
    double t = 0;
    int step = 0;

    while (t < tend) {

        stromer(particles, Fo, grid, rc, cellSize, nx, ny);

        // ===== Export VTK =====
        std::ofstream file("out_" + std::to_string(step) + ".vtk");

        file << "# vtk DataFile Version 3.0\n";
        file << "Particles\n";
        file << "ASCII\n";
        file << "DATASET POLYDATA\n";

        file << "POINTS " << particles.size() << " float\n";

        for (auto& p : particles) {
            file << p.getPosition()[0] << " "
                 << p.getPosition()[1] << " 0\n";
        }

        file << "VERTICES " << particles.size() << " " << 2 * particles.size() << "\n";

        for (int i = 0; i < particles.size(); i++) {
            file << "1 " << i << "\n";
        }

        file.close();

        t += dt;
        step++;

        if (step % 100 == 0)
            std::cout << "t = " << t << std::endl;
    }

    std::cout << "Simulation terminee !" << std::endl;

    return 0;
}