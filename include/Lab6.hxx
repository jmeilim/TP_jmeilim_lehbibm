#pragma once

#include <vector>
#include <string>
#include "Lab2.hxx"

enum BoundaryType {
    REFLEXION,
    ABSORPTION,
    PERIODIQUE
};

bool conditionLimites(Particle& p, double Lx, double Ly, BoundaryType type) ;