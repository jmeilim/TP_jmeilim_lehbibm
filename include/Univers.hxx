#pragma once
#include <vector>
#include "Cellule.hxx"
#include "particle.hxx"
/**
 * @brief claase pour representer l'univers de simulation
 */
class Univers {

    double eps;   ///< profondeur du potentiel
    double sig;  ///< distance caractéristique
    int  dim;     ///< dimension 
    double ld;    ///< taille de la boîte
    double rc;   ///< rayon de coupure
    std::vector< Cellule > grid ;    ///Maillage de l'nivers
    std::vector< Particle > particules ;   ///liste des particules


public:   
    Univers(double eps, double sig, int dim,
            double Lx, double Ly, double rc);

    double getEps() const ;
    double getSig() const ;
    int getDim() const ;
    double getLx() const;
    double getLy() const;
    double getRc() const ;
    int getNx() const;
    int getNy()  const;
    double getCellSize() const;


    std::vector<Cellule>& getGrid ();


    void setEps(double e);
    void setSig(double s);
    void setDim(int d);
    void setLx(double l);
    void setLy(double l);
    void setRc(double r);
    
};