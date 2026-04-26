#include <string> 
#include <iostream>
#include <chrono>
#include "../include/Lab3.hxx"
#include "../include/Lab2.hxx"




/**
 * @brief classe représente l'univers contenant toutes les particules
 * 
 */
class Univer {

private:

    int dimension; ///< dimension de l'espace (1D, 2D, 3D)
    int nbParticles; ///< liste des particules

    std::vector<Particle> particles;

public:
    /**
     * @brief Constructeur de Univers
     * @param dimension dimension de l'espace
     */
    Univer(int dimension) : dimension(dimension) {}


    /**
     * @brief Ajoute une particule à l'univers
     * @param p particule à ajouter
     */
    void addParticle(const Particle& p)
    {
        particles.push_back(p);
        nbParticles = particles.size();
    }


    /**
     * @brief Acces aux particules
     * @return liste des particules
     */
    std::vector<Particle>& getParticles()
    {
        return particles;
    }


     /**
     * @brief Retourne le nombre de particules
     */
    int getNbParticles() const
    {
        return nbParticles;
    }



    /**
     * @brief Affiche les positions des particules
     */    
    void afficher() const
    {
        for(const auto& p : particles)
        {
            std::cout << p.getPosition()[0] << " "
                      << p.getPosition()[1] << " "
                      << p.getPosition()[2] << "\n";
        }
    }
};
