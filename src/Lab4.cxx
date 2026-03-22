#include <iostream>
#include <fstream>
#include <cmath>

double U(double r, double eps = 1, double sig = 1){
    return 4 * eps * pow(sig/r,6) *( pow(sig/r,6)-1);
}

class Univers {
public:
    double eps ;
    double sig;
    double dim ;
    double ld;
    double rc;
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