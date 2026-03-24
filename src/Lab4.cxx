#include <iostream>
#include <fstream>
#include <cmath>



/**
 * @brief Potentiel de Lennard-Jones
 */
double U(double r, double eps = 1, double sig = 1){
    return 4 * eps * pow(sig/r,6) *( pow(sig/r,6)-1);
}


/**
 * @brief claase pour representer l'univers de simulation
 */
class Univers {
public:
    double eps;   ///< profondeur du potentiel
    double sig;  ///< distance caractéristique
    int  dim;     ///< dimension 
    double ld;    ///< taille de la boîte
    double rc;   ///< rayon de coupure
    
    Univers(double e, double s, int dimension, double l, double rcut)
        : eps(e), sig(s), dim(dimension), ld(l), rc(rcut) {}
};


int main() {
    std:: ofstream file("lab.dat");
    double rm=0.3;
    double rmm=3.0;
    int N = 500;
    for (int i = 0; i < 500; i++){
        double r = rm + (rmm - rm) * i / (N - 1);
        double res = U(r);
        file << r << " " << res << std::endl;
    }
    return 0;
}