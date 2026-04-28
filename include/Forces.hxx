
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
Vector forceReflexivePotentiel(const Particle& p,
                                double Lx, double Ly,
                                double epsilon, double sigma);


inline double U(double r, double eps , double sig );