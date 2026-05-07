

#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

#include "../include/Particle.hxx"
#include "../include/Vector.hxx"
#include "../include/Cellule.hxx"
#include "../include/Stromer.hxx"
#include "../include/Forces.hxx"
#include "../include/Univers.hxx"
#include "../include/Boundary.hxx"
#include "../include/GenereException.hxx"



/**
 * Simulation de la collision entre un disque et un rectangle (lab6a).
 *
 * Paramètres conformes au sujet :
 *   - domaine       : Lx=250, Ly=180
 *   - potentiel LJ  : eps=1, sigma=1, rc=2.5*sigma
 *   - pas de temps  : dt=0.0005
 *   - gravité       : G=-12 (définie dans Forces.cxx)
 *   - thermostat    : Ec_target = 0.005 * N_rect (toutes les 1000 itérations)
 *
 * Conditions aux limites choisies :
 *   - gauche/droite : réflexion — les particules rebondissent sur les parois latérales
 *   - bas           : réflexion simple + potentiel LJ de paroi (forceMurBas)
 *                     appliqué uniquement aux "rect" pour simuler un sol solide
 *   - haut          : absorption — les particules éjectées vers le haut
 *                     quittent définitivement la simulation
 *
 * Ce choix de conditions asymétriques (réflexion bas, absorption haut)
 * correspond au comportement physique attendu : le rectangle repose sur le sol,
 * le disque tombe .
 */

int main() {
    try{
        double sigma   = 1.0;
        double epsilon = 1.0;   
        double d       = pow(2.0, 1.0/6.0) * sigma; // distance inter-particules = 2^(1/6)*sigma

        double rc   = 2.5 * sigma;
        double dt   = 0.0005;
        double tend = 10;

        double lx = 250.0;  
        double ly = 180.0;

        int dim = 2;
        Univers univer(epsilon, sigma, dim, lx, ly, rc);

    


        // ── Rectangle ────────────────────────────────────────────────────────
        // On remplit un rectangle de 50 lignes × Nx colonnes de particules
        // équidistribuées à la distance d = 2^(1/6)*sigma.
        // Nx = floor(Lx / d) ≈ 222 colonnes → ~11100 particules au total.
        // Ces particules sont catégorisées "rect" : elles sont soumises
        // au thermostat et au potentiel de paroi basse (forceMurBas).

        int Nx = (int)(lx / d);
        double blockHeight = 77.0 * d; 

        for (int i = 0; i < Nx; i++) {
            for (int j = 0; j < 50; j++) {  
                Vector pos((i + 0.5) * d, (j + 0.5) * d, 0);
                Vector vel(0, 0, 0);
                univer.addParticle(
                    Particle(pos, vel, 1.0,
                            univer.getNbParticles(),
                            Vector(0,0,0), "rect")
                );
            }
        }

    



        // ── Disque ───────────────────────────────────────────────────────────
        // On génère un disque de rayon R = 10*d centré au-dessus du rectangle,
        // avec un espace gap = 2*d pour éviter une superposition initiale
        // qui causerait des forces LJ infinies au premier pas.
        // La vitesse initiale (0, -10) simule la chute vers le rectangle.
        // Ces particules sont catégorisées "disk" : elles ne sont pas soumises
        // au thermostat et peuvent s'échapper par le bord haut (absorption).


        double centerX = lx / 2.0;
        double R       = 10 * d;
        double gap     = 2.0 * d;
        double centerY = blockHeight + R + gap;

        for (int i = -20; i <= 20; i++) {
            for (int j = -20; j <= 20; j++) {
                double dx = i * d;
                double dy = j * d;
                if (dx*dx + dy*dy <= R*R) {
                    Vector pos(centerX + dx, centerY + dy, 0);
                    Vector vel(0, -10, 0);
                    univer.addParticle(
                        Particle(pos, vel, 1.0,
                                univer.getNbParticles(),
                                Vector(0,0,0), "disk")
                    );
                }
            }
        }
        std::cout << "Nombre de particules : "
                << univer.getNbParticles() << std::endl;

        // ── Initialisation des forces ─────────────────────────────────────────
        // On calcule les forces initiales avant de lancer la boucle
        // car Störmer-Verlet a besoin de F(t=0) pour la première itération

        std::vector<Vector> Fo(univer.getNbParticles(), Vector(0,0,0));

        univer.updateCells();

        auto& particles = univer.getParticles();
        auto& grid      = univer.getGrid();

        for (int i = 0; i < univer.getNbParticles(); i++) {
            if (!particles[i].isAlive()) continue;  
            Fo[i] = computeForce(
                particles[i], particles,
                univer.getRc(), grid,
                univer.getCellSize(),
                univer.getNx(), univer.getNy()
            );
        }

    

        // ── Boucle principale ─────────────────────────────────────────────────
        // On sauvegarde un fichier VTK tous les 100 pas pour visualiser
        // l'évolution sous ParaView sans générer trop de fichiers

        double t    = 0.0;
        int    step = 0;
        std::vector<int> savedSteps;
        while (t < tend) {
            stromer(univer, Fo, dt, step);
            
            if (step % 100 == 0) {

                auto& particles = univer.getParticles();

                std::ofstream file("../demo/out_" + std::to_string(step) + ".vtk");
                if (!file.is_open())
                    throw GenereException("Impossible d'ouvrir : ../demo/out_"
                                          + std::to_string(step) + ".vtk");
                file << "# vtk DataFile Version 3.0\n";
                file << "Particles\n";
                file << "ASCII\n";
                file << "DATASET POLYDATA\n";

                // on ne sauvegarde que les particules encore actives
                std::vector<int> active;
                for (int i = 0; i < (int)particles.size(); i++)
                    if (particles[i].isAlive())
                        active.push_back(i);

                int N = active.size();

                file << "POINTS " << N << " float\n";
                for (int idx : active) {
                    auto& p = particles[idx];
                    file << p.getPosition()[0] << " "
                        << p.getPosition()[1] << " 0\n";
                }

                file << "VERTICES " << N << " " << 2*N << "\n";
                for (int i = 0; i < N; i++)
                    file << "1 " << i << "\n";

                file << "POINT_DATA " << N << "\n";
                file << "SCALARS type int 1\n";
                file << "LOOKUP_TABLE default\n";

                
                for (int idx : active) {
                    file << (particles[idx].getCat() == "disk" ? 1 : 0) << "\n";
                }

                file.close();
                savedSteps.push_back(step);
            }

            t += dt;
            step++;

            if (step % 1000 == 0)
                std::cout << "t = " << t << std::endl;
        }



        // ── Fichier série VTK ─────────────────────────────────────────────────
        // Ce fichier permet à ParaView de charger tous les pas de temps
        // en une seule opération et d'animer la simulation

        
        std::ofstream series("../demo/out.vtk.series");
        series << "{ \"file-series-version\" : \"1.0\", \"files\" : [\n";
        for (size_t i = 0; i < savedSteps.size(); i++) {
            series << "  { \"name\" : \"out_" << savedSteps[i]
                << ".vtk\", \"time\" : " << savedSteps[i] << " }";
            if (i != savedSteps.size() - 1) series << ",";
            series << "\n";
        }
        series << "]}\n";
        series.close();

        std::cout << "Simulation terminee !" << std::endl;
        return 0;
    } catch (const GenereException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "erreur inattendue " << e.what() << std::endl;
        return 2;
    }
}