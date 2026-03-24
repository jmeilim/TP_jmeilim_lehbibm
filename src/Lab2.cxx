#include <string> 
#include<set>
#include<list>
#include<deque>
#include<vector>
#include <random>
#include <iostream>
#include <chrono>
#include "../include/Lab3.hxx"


    /** 
     * @brief 
     * 
     * 
     */

class Particle {
    private :


    Vector position;  ///< position de la particule
    Vector vitesse;   ///< vitesse de la particule
    int masse;        ///< masse
    int id;           ///< identifiant unique
    Vector force;     ///< force appliquée
    std::string cat;  ///< catégorie

    /**
     * @brief Constructeur de la particule
     * 
     * @param position position initiale
     * @param vitesse vitesse initiale
     * @param masse masse de la particule
     * @param id identifiant unique
     * @param force force initiale
     * @param cat catégorie de la particule
     */  
    
     
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
Vector computeForce(Particle &p, std::vector<Particle>& ps);


/**
 * @brief Implementation du Stromer-Algorithm
 * 
 * @param particleList 
 * @param Fo 
 * @return double* 
 */
void stromer(std::vector<Particle> & particleList, std::vector< Vector >& Fo ){
    double dt = 0.015; 
    double tend = 468.5 ;
    int N = particleList.size();
    std::vector<Vector> F(N , Vector(0.0,0.0 ,0.0) ) ;
    for ( int i=0 ; i< N; i++){
        F[i]=computeForce(particleList[i] , particleList); 
    }

    int dim = particleList[0].getPosition().size();
    double t = 0 ; 
    while ( t < tend ){
        t+= dt ; 
        for ( int i=0 ; i< N; i++){
            for ( int d = 0 ; d<dim; d++){
                particleList[i].getPosition()[d]+= dt * ( particleList[i].getVitesse()[d] + (0.5 / particleList[i].getMasse())*dt*F[i][d]) ;
                Fo[i][d]= F[i][d] ;  
            }
        }
        
        for ( int i=0 ; i< N; i++){
            F[i]=computeForce(particleList[i] , particleList); 
        }
        for ( int i=0 ; i< N; i++){
            for ( int d = 0 ; d<dim; d++){
        particleList[i].getVitesse()[d]+= (0.5 / particleList[i].getMasse())*(F[i][d] + Fo[i][d])*dt ; 
            }
        }
    }
}

/**
 * @brief Calcule la force gravitationnelle sur une particule
 * 
 * @param p particule cible
 * @param ps liste des particules
 * @return Vector force résultante
 */
Vector computeForce( Particle& p  , std::vector<Particle> &ps ){
   
    for ( int j = 0 ; j<ps.size() ; j++){
        if ( ps[j].getId() != p.getId() ){
            for ( int d = 0 ; d<2 ; d++){
                p.getForce()[d] += p.getMasse() * ps[j].getMasse() * ( ps[j].getPosition()[d] - p.getPosition()[d] ) / pow( (pow(ps[j].getPosition()[0] - p.getPosition()[0],2) + pow(ps[j].getPosition()[1] - p.getPosition()[1],2) ) , 1.5 ) ;
            }
        }
    }
    return p.getForce() ; 
}
