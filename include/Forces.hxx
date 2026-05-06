
#pragma once
#include <vector>
#include "Particle.hxx"
#include "Cellule.hxx"


Vector computeForce(const Particle& p,
                    std::vector<Particle>& ps,
                    double rc,
                    std::vector<Cellule>& grid,
                    double cellSize,
                    int nx,
                    int ny);
Vector forceMurBas(const Particle& p,
                   double epsilon,
                   double sigma);


inline double U(double r, double eps , double sig );

Vector computeGravity(const Particle& p, double G);