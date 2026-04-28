#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <Cellule.hxx>
/**
 * @brief claase pour representer l'univers de simulation
 */
class Univers {

    double eps;   ///< profondeur du potentiel
    double sig;  ///< distance caractéristique
    int  dim;     ///< dimension 
    double ld;    ///< taille de la boîte
    double rc;   ///< rayon de coupure
    std::vector< Cellule* > cellules ; 
public:   
    Univers(double e, double s, int dimension, double l, double rcut,std::vector< Cellule* > cellules )
        : eps(e), sig(s), dim(dimension), ld(l), rc(rcut) , cellules(cellules) {}
    Univers(double e, double s, int dimension, double l, double rcut)
    : eps(e), sig(s), dim(dimension), ld(l), rc(rcut), cellules() {}


    double geteps() const ;
    double getsig() const ;
    int getdim() const ;
    double getld() const;
    double getrc() const ;
    int getNx() const;
    int getNy()  const;
    double getCellSize() const;


    std::vector<Cellule*>& getCellules() {
        return cellules;
    }


    void seteps(double e);
    void setsig(double s);
    void setdim(int d);
    void setld(double l);
    void setrc(double r);
    
};