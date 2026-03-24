#include <string> 
#include <random>
#include <iostream>
#include <chrono>
#include "../include/Lab3.hxx"
#include "../include/Lab2.hxx"


Vector computeForce(const Particle& p, std::vector<Particle>& ps);


/**
 * @brief Implementation du Stromer-Algorithm
 * 
 * @param particleList liste des particules 
 * @param Fo  Fo vecteur des forces précédentes
 */

void stromer(std::vector<Particle> & particleList, std::vector<Vector> &Fo) {
    double dt = 0.001;
    double tend = 468.5;
    int N = particleList.size();

    std::vector<Vector> F(N, Vector(0.0,0.0,0.0));

    for (int i = 0; i < N; i++)
        F[i] = computeForce(particleList[i], particleList);

    double t = 0;

    while (t < tend) {
        t += dt;

        for (int i = 0; i < N; i++) {
            double m = particleList[i].getMasse();
            if (m < 1e-12) m = 1e-12;

            for (int d = 0; d < 2; d++) {
                particleList[i].getPosition()[d] += dt * particleList[i].getVitesse()[d]
                    + 0.5 * dt * dt * F[i][d] / m;
            }
        }

        for (int i = 0; i < N; i++)
            Fo[i] = F[i];

        for (int i = 0; i < N; i++)
            F[i] = computeForce(particleList[i], particleList);

        for (int i = 0; i < N; i++) {
            double m = particleList[i].getMasse();
            if (m < 1e-12) m = 1e-12;

            for (int d = 0; d < 2; d++) {
                particleList[i].getVitesse()[d] +=
                    0.5 * dt * (F[i][d] + Fo[i][d]) / m;
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
Vector computeForce(const Particle& p, std::vector<Particle>& ps) {
    Vector F(0.0, 0.0, 0.0);

    for (int j = 0; j < ps.size(); j++) {
        if (ps[j].getId() != p.getId()) {

            double dx = ps[j].getPosition()[0] - p.getPosition()[0];
            double dy = ps[j].getPosition()[1] - p.getPosition()[1];

            double r2 = dx*dx + dy*dy + 1e-12;
            double inv_r3 = 1.0 / (r2 * sqrt(r2));

            F[0] += ps[j].getMasse() * dx * inv_r3;
            F[1] += ps[j].getMasse() * dy * inv_r3;
        }
    }

    return F;
}
