#pragma once
#include <vector>
#include "Cellule.hxx"
#include "Particle.hxx"
/**
 * @brief claase pour representer l'univers de simulation
 */
class Univers {

    double eps;   ///< profondeur du potentiel
    double sig;  ///< distance caractéristique
    int  dim;     ///< dimension 
    double lx;    ///< taille de la boîte suivant l'axe x
    double ly;    ///< taille de la boîte suivant l'axe y
    double rc;   ///< rayon de coupure
    double cellSize; /// TIlle des cellules
    int nx;    
    int ny;    
    std::vector< Cellule > grid ;    ///Maillage de l'nivers
    std::vector< Particle > particles ;   ///liste des particules


public:   
    Univers(double eps, double sig, int dim,
            double Lx, double Ly, double rc);



    std::vector<Cellule>& getGrid ();
    std::vector<Particle>& getParticles();

    void addParticle(const Particle& p);
    int  getNbParticles() const;
    void initialiserGrille();
    void updateCells();
    double getEps() const ;
    double getSig() const ;
    int getDim() const ;
    double getLx() const;
    double getLy() const;
    double getRc() const ;
    int getNx() const;
    int getNy()  const;
    double getCellSize() const;


    
 
    void setEps(double e);
    void setSig(double s);
    void setRc(double r);
    
};