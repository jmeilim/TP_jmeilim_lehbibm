#pragma once

#include <vector>
#include <string>
#include "Lab3.hxx"

    /** 
     * @brief Classe représentante une particule dans la simulation
     * 
     */
class Particle {
    private :


    Vector position;  ///< position de la particule
    Vector vitesse;   ///< vitesse de la particule
    double masse;     ///< masse
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
    public :Particle ( Vector position ,Vector vitesse, double masse, int id ,   Vector force  ,  std::string cat  )
        : position(position) , vitesse(vitesse), masse (masse) , id(id) ,force(force) ,cat(cat) {}


    public :

    /// @brief Accès modifiable position
    Vector getPosition() const { return position; }
    
    /// @brief Accès modifiable vitesse
    Vector getVitesse() const { return vitesse; }
    
    /// @brief Accès lecture position
    Vector& getPosition() { return position; }
    
    /// @brief Accès lecture vitesse
    Vector& getVitesse() { return vitesse; }
    
    /// @brief Accès modifiable force
    Vector& getForce() { return force; }
    
    /// @brief Retourne la masse
    double getMasse() const { return masse; }
    
    /// @brief Retourne l'identifiant
    int getId() const { return id; }
    
    /// @brief Accès lecture force
    Vector getForce() const { return force; }
    
    /// @brief Retourne la catégorie
    std::string getCat() const { return cat; }
    
};

Vector computeForce(const Particle& p, std::vector<Particle>& ps);
void stromer(std::vector<Particle>& particleList, std::vector<Vector>& Fo);