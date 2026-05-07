#pragma once

#include "Particle.hxx"


void reflexion (Particle& p, double Lx, double Ly);
void absorption(Particle& p, double Lx, double Ly);
void periodique (Particle& p, double Lx, double Ly);
bool conditionLimites(Particle& p, double Lx, double Ly);