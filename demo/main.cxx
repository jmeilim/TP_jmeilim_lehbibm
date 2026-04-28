#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

#include "../include/Particle.hxx"
#include "../include/Vector.hxx"
#include "../include/Cellule.hxx"
#include "../include/Stromer.hxx"
#include "../include/Forces.hxx"
#include "../include/Univers.hxx"

int main() {

    double sigma = 1.0;
    double epsilon = 5.0;
    double d = pow(2.0, 1.0/6.0) * sigma;

    double rc = 2.5 * sigma;
    double dt = 0.001;
    double tend = 7;

    double gap = 6.0;

    double lx = 160*d ;
    double ly = 80*d + gap;

    Univers univer(epsilon,sigma,2, lx,ly,rc);

    for (int i = 0; i < 160; i++) {
        for (int j = 0; j < 40; j++) {
            Vector pos((i+0.5) * d, (j+0.5) * d, 0);  
            Vector vel(0, 0, 0);
            univer.addParticle(
                Particle(pos, vel, 1.0, univer.getNbParticles(), Vector(0,0,0), "rect")
            );
        }
    }

    double centerX = (160 * d) / 2.0; 
    double squareWidth = 40 * d;
    double squareStartY = 40 * d + gap;  
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            Vector pos(centerX - squareWidth / 2 + i * d, squareStartY + j * d, 0);
            Vector vel(0, -10, 0);
            univer.addParticle(
                Particle(pos, vel, 1.0, univer.getNbParticles(), Vector(0,0,0), "square")
            );
        }
    }

   

    
    std::vector<Vector> Fo(univer.getNbParticles(), Vector(0,0,0));

    
    univer.updateCells();
    for (int i = 0; i < univer.getNbParticles(); i++)
        Fo[i] = Fo[i]=computeForce(univer.getParticles()[i],univer.getParticles(),univer.getRc(),
                                    univer.getGrid(),univer.getCellSize(),univer.getNx(),univer.getNy());

    double t = 0;
    int step = 0;
    std::vector<int> savedSteps;
    while (t < tend) {

        stromer(univer, Fo,dt);
        auto& particles=univer.getParticles();
        if (step % 100 == 0) {
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