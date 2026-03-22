#include <string> 
#include<set>
#include<list>
#include<deque>
#include<vector>
#include <random>
#include <iostream>
#include <chrono>
#include "../include/Lab3.hxx"

class Particle {
    private :

    // Les attribus

    Vector position ; 
    Vector vitesse ; 
    int masse ; 
    int id ; 
    Vector force ; 
    std::string cat ; 

    // Constructeur
    
    public :Particle ( Vector position ,Vector vitesse, int masse, int id ,   Vector force  ,  std::string cat  )
        : position(position) , vitesse(vitesse), masse (masse) , id(id) ,force(force) ,cat(cat) {}


    public :
    Vector getPosition() const { return position; }
    Vector getVitesse() const { return vitesse; }
    Vector& getPosition() { return position; }
    Vector& getVitesse() { return vitesse; }
    Vector& getForce() { return force; }
    int getMasse() const { return masse; }
    int getId() const { return id; }
    Vector getForce() const { return force; }
    std::string getCat() const { return cat; }
    
};
Vector computeForce(Particle p, std::vector<Particle>& ps);



// Implementation du Stromer-Algorithm

double *stromer(std::vector<Particle> & particleList, std::vector< Vector > Fo ){
    double dt = 0.015; 
    double tend = 468.5 ;
    int N = particleList.size();
    std::vector<Vector> F(N , Vector(0.0,0.0 ,0.0) ) ;
    for ( int i=0 ; i< N; i++){
        F[i]=computeForce(particleList[i] , particleList); 
    }
    double t = 0 ; 
    while ( t < tend ){
        t+= dt ; 
        for ( int i=0 ; i< N; i++){
            for ( int d = 0 ; d<2 ; d++){
                particleList[i].getPosition()[d]+= dt * ( particleList[i].getVitesse()[d] + (0.5 / particleList[i].getMasse())*dt*F[i][d]) ;
                Fo[i][d]= F[i][d] ;  
            }
        }
        
    }
    for ( int i=0 ; i< N; i++){
        F[i]=computeForce(particleList[i] , particleList); 
    }
    for ( int i=0 ; i< N; i++){
        for ( int d = 0 ; d<2 ; d++){
       particleList[i].getVitesse()[d]+= (0.5 / particleList[i].getMasse())*(F[i][d] + Fo[i][d])*dt ; 
        }
    }
    return nullptr ;
}

 Vector computeForce( Particle p  , std::vector<Particle> &ps ){
   
    for ( int j = 0 ; j<ps.size() ; j++){
    if ( ps[j].getId() != p.getId() ){
        for ( int d = 0 ; d<2 ; d++){
            p.getForce()[d] += p.getMasse() * ps[j].getMasse() * ( ps[j].getPosition()[d] - p.getPosition()[d] ) / pow( (pow(ps[j].getPosition()[0] - p.getPosition()[0],2) + pow(ps[j].getPosition()[1] - p.getPosition()[1],2) ) , 1.5 ) ;

    }
   
    
    }
    }
    return p.getForce() ; 
}



// int main() {
    
//     auto start = std::chrono::steady_clock::now();
//     std::vector<Particle> particles = {

//     Particle(Vector(0,0,0), Vector(0,0,0), 1, 0, Vector(0,0,0), "Soleil"),

//     Particle(Vector(0,1,0), Vector(-1,0,0), 3.0e-6, 1, Vector(0,0,0), "Terre"),

//     Particle(Vector(0,5.36,0), Vector(-0.425,0,0), 9.55e-4, 2, Vector(0,0,0), "Jupiter"),

//     Particle(Vector(34.75,0,0), Vector(0,0.0296,0), 1.0e-14, 3, Vector(0,0,0), "Halley")

//     };
//     std::vector<Vector> Fo = { Vector(1.0e-14,1.0e-14 , 1.0e-14) , Vector(1.0e-14,1.0e-14 , 1.0e-14) , Vector(1.0e-14,1.0e-14 , 1.0e-14) , Vector(1.0e-14,1.0e-14 , 1.0e-14) } ;

//     stromer(particles, Fo);



//     auto end = std::chrono::steady_clock::now();
//     std::chrono::duration<double> elapsed_seconds = end-start;
//     std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
//     return 0; 
//  }

