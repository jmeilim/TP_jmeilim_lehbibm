#include <iostream>
#include <fstream>
#include "../include/Lab2.hxx"
#include "../include/Lab4.hxx"
#include "../include/Lab6.hxx"

bool conditionLimites(Particle& p, double Lx, double Ly, BoundaryType type) {

    Vector& pos = p.getPosition();
    Vector& vel = p.getVitesse();

    double x = pos.getX();
    double y = pos.getY();

    if (type == REFLEXION) {

    
        if (x < 0) {
            pos.setX(-x);
            vel.setX(-vel.getX());
        }
        if (x > Lx) {
            pos.setX(2 * Lx - x);
            vel.setX(-vel.getX());
        }


        if (y < 0) {
            pos.setY(-y);
            vel.setY(-vel.getY());
        }
        if (y > Ly) {
            pos.setY(2 * Ly - y);
            vel.setY(-vel.getY());
        }

        return true;
    }

    else if (type == ABSORPTION) {

    if (x < 0 || x > Lx || y < 0 || y > Ly) {
        p.setAlive(false);
    }
    }

    else if (type == PERIODIQUE) {

        
        if (x < 0) pos.setX(x + Lx);
        if (x > Lx) pos.setX(x - Lx);

        
        if (y < 0) pos.setY(y + Ly);
        if (y > Ly) pos.setY(y - Ly);

        return true;
    }

    return true;
}