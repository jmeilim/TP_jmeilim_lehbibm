#pragma once
#include "Vector.hxx"
#include <string>

/** 
     * @brief Classe représentante une particule dans la simulation
     * 
*/
class Particle {

    Vector position;  ///< position de la particule
    Vector vitesse;   ///< vitesse de la particule
    double masse;     ///< masse
    int id;           ///< identifiant unique
    Vector force;     ///< force appliquée
    std::string cat;  ///< catégorie
    bool alive ;

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
    public :Particle ( Vector position ,Vector vitesse, double masse, int id ,   Vector force  ,  std::string cat  )
        : position(position) , vitesse(vitesse), masse (masse) , id(id) ,force(force) ,cat(cat) ,alive(true) {}


    public :
    Vector& getPosition();
    const Vector& getPosition() const;

    Vector& getVitesse();
    const Vector& getVitesse() const;

    Vector& getForce();
    const Vector& getForce() const;
    
    double getMasse() const { return masse; }
    int getId() const { return id; }
    std::string getCat() const { return cat; }
    bool isAlive() const { return alive; }
    void setAlive(bool a) { alive = a; }
    
};

