#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

#include "../include/Lab2.hxx"
#include "../include/Lab4.hxx"

int main() {

    double sigma = 1.0;
    double d = pow(2.0, 1.0/6.0) * sigma;

    double rc = 2.5 * sigma;
    double dt = 0.00005;
    double tend = 7;

    std::vector<Particle> particles;

    double marginX = 30.0;
    double marginY = 30.0;
    for (int i = 0; i < 160; i++) {
        for (int j = 0; j < 40; j++) {
            Vector pos(marginX + i * d, marginY + j * d, 0);  
            Vector vel(0, 0, 0);
            particles.push_back(
                Particle(pos, vel, 1.0, particles.size(), Vector(0,0,0), "rect")
            );
        }
    }

    double centerX = marginX + (160 * d) / 2.0; 
    double squareWidth = 40 * d;
    double rectHeight = 40 * d;
    double gap = 6.0;
    double squareStartY = marginY + rectHeight + gap;  
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            Vector pos(centerX - squareWidth / 2 + i * d, squareStartY + j * d, 0);
            Vector vel(0, -10, 0);
            particles.push_back(
                Particle(pos, vel, 1.0, particles.size(), Vector(0,0,0), "square")
            );
        }
    }

    double Lx = 160 * d + 2 * marginX;            
    double Ly = 40 * d + 40 * d + gap + 2 * marginY; 
    int nx = (int)(Lx / rc);
    int ny = (int)(Ly / rc);
    double cellSize = rc;

    std::vector<Cellule> grid(nx * ny);

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            grid[i * ny + j].center = Vector(
                (i + 0.5) * cellSize,
                (j + 0.5) * cellSize,
                0
            );
        }}
    std::vector<Vector> Fo(particles.size(), Vector(0,0,0));

    double t = 0;
    int step = 0;
    std::vector<int> savedSteps;

    updateCells(grid, particles, cellSize, nx, ny);
    for (int i = 0; i < (int)particles.size(); i++)
        Fo[i] = computeForce(particles[i], particles, rc, grid, cellSize, nx, ny);

    while (t < tend) {

        stromer(particles, Fo, grid, rc, cellSize, nx, ny,dt);

        if (step % 500 == 0) {
        std::ofstream file("../demo/out_" + std::to_string(step) + ".vtk");

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

        for (int i = 0; i < (int) particles.size(); i++) {
            file << "1 " << i << "\n";
        }

        file << "POINT_DATA " << particles.size() << "\n";
        file << "SCALARS velocity float 1\n";
        file << "LOOKUP_TABLE default\n";

        for (auto& p : particles) {
            double vx = p.getVitesse()[0];
            double vy = p.getVitesse()[1];

            double v = sqrt(vx*vx + vy*vy);

            file << v << "\n";
        }
        file.close();
        savedSteps.push_back(step);
    }
        t += dt;
        step++;

        if (step % 1000 == 0)
            std::cout << "t = " << t << std::endl;
    }

    std::ofstream series("../demo/out.vtk.series");

    series << "{ \"file-series-version\" : \"1.0\", \"files\" : [\n";
    for (size_t i = 0; i < savedSteps.size(); i++) {
        series << "  { \"name\" : \"out_" << savedSteps[i] << ".vtk\", \"time\" : " << savedSteps[i] << " }";
        if (i != savedSteps.size() - 1)
            series << ",";
        series << "\n";
    }
    series << "]}\n";
    series.close();

    std::cout << "Simulation terminee !" << std::endl;

    return 0;
}