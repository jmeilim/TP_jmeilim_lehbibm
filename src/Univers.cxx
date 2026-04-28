#include <cmath>
#include "../include/Univers.hxx"
/**
 * @brief claase pour representer l'univers de simulation
 */
  
Univers::Univers(double eps, double sig, int dimension,
                double lx, double ly, double rc)
                : eps(eps), sig(sig), dim(dimension), lx(lx),ly(ly), rc(rc) ,nx((int)(lx / rc)),
                  ny((int)(ly / rc)), cellSize(rc) { initialiserGrille();}


double Univers::getEps() const {return eps;} ;
double Univers::getSig() const {return sig;};
int Univers::getDim() const {return dim;};
double Univers::getLx() const {return lx;};
double Univers::getLy() const {return ly;};
double Univers::getRc() const {return rc;};
int Univers::getNx() const {return nx;};
int Univers::getNy() const {return ny;};
double Univers::getCellSize() const {return cellSize;};
int Univers::getNbParticles() const { return (int)particles.size();};

std::vector<Cellule>& Univers::getGrid() { return grid;}
std::vector<Particle>& Univers::getParticles() { return particles;}

void Univers::setEps(double e){eps =e;};
void Univers::setSig(double s){sig = s;};
void Univers::setRc(double r){rc = r;};


void Univers::addParticle(const Particle& p) {
    particles.push_back(p);
}


void Univers::initialiserGrille() {
    grid.resize(nx * ny);
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            grid[i * ny + j].center = Vector(
                (i + 0.5) * cellSize,
                (j + 0.5) * cellSize,
                0
            );
        }}
}


void Univers::updateCells() {
    for (auto& c : grid)
        c.particles.clear();

    for (int i = 0; i < (int )particles.size(); i++) {
        int cx = particles[i].getPosition()[0] / cellSize;
        int cy = particles[i].getPosition()[1] / cellSize;
        if (cx < 0 || cy < 0 || cx >= nx || cy >= ny) continue;
        int id = cx * ny + cy;
        grid[id].particles.push_back(i);
    }
}
