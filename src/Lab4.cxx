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
#include <fstream>


int main(){
    
    Particle P1 = Particle(Vector(0,5.36,0), Vector(-0.425,0,0), 9.55e-4, 2, Vector(9.55e4,9.55e4,0), "Jupiter") ; 
    Particle P2 = Particle(Vector(0,0,0), Vector(0,0,0), 1, 0, Vector(0,0,0), "Soleil") ; 

    std::ofstream file("particules.txt") ; 

    file << P1.getPosition().getX() << " " << P1.getPosition().getY() << " " << P1.getCat() << std::endl;
    file << P2.getPosition().getX() << " " << P2.getPosition().getY() << " " << P2.getCat() << std::endl;

    file.close(); 






    return 0 ; 
}