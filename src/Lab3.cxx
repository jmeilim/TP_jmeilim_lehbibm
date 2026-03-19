#include <string> 
#include<set>
#include<list>
#include<deque>
#include<vector>
#include <random>
#include <iostream>
#include <chrono>
#include <cmath>
#include "../include/Lab3.hxx"
#include "Lab2.cxx"


class Univers {

private:

    int dimension;
    int nbParticles;
    std::vector<Particle> particles;

public:

    Univers(int dimension) : dimension(dimension) {}

    void addParticle(const Particle& p)
    {
        particles.push_back(p);
        nbParticles = particles.size();
    }

    std::vector<Particle>& getParticles()
    {
        return particles;
    }

    int getNbParticles() const
    {
        return nbParticles;
    }

    void afficher() const
    {
        for(const auto& p : particles)
        {
            std::cout << p.getPosition()[0] << " "
                      << p.getPosition()[1] << " "
                      << p.getPosition()[2] << "\n";
        }
    }
};



int main() {
    auto start = std::chrono::steady_clock::now();

    std::vector<Particle> particles = {

    Particle(Vector(0,0,0), Vector(0,0,0), 1, 0, Vector(0,0,0), "Soleil"),

    Particle(Vector(0,1,0), Vector(-1,0,0), 3.0e-6, 1, Vector(0,0,0), "Terre"),

    Particle(Vector(0,5.36,0), Vector(-0.425,0,0), 9.55e-4, 2, Vector(0,0,0), "Jupiter"),

    Particle(Vector(34.75,0,0), Vector(0,0.0296,0), 1.0e-14, 3, Vector(0,0,0), "Halley")

    };
    std::vector<Vector> Fo = { Vector(1.0e-14,1.0e-14 , 1.0e-14) , Vector(1.0e-14,1.0e-14 , 1.0e-14) , Vector(1.0e-14,1.0e-14 , 1.0e-14) , Vector(1.0e-14,1.0e-14 , 1.0e-14) } ;

    stromer(particles, Fo);

    Univers u(3);
    int N = 1 << 25 ; 
    for ( int i = 0 ; i< N ; i++){
        u.addParticle( Particle( Vector(i,i,i) , Vector(1,1,1) , 1.0e-14 , i , Vector(0,0,0) , "Uniforme" ) ) ;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0 ;
}