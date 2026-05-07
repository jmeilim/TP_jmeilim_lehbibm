# TP_jmeilim_lehbibm
# Simulation Particulaire

> Grenoble INP — MMIS — Printemps 2026  
> Auteurs : **jmeili-m** · **lehbibm**

Simulation moléculaire 2D d'une collision entre un disque et un rectangle,
utilisant le potentiel de **Lennard-Jones** et l'algorithme de **Störmer-Verlet**.

---

## Table des matières

- [TP\_jmeilim\_lehbibm](#tp_jmeilim_lehbibm)
- [Simulation Particulaire](#simulation-particulaire)
  - [Table des matières](#table-des-matières)
  - [Compilation et exécution](#compilation-et-exécution)
    - [Compiler](#compiler)
    - [Lancer la simulation](#lancer-la-simulation)
    - [Lancer les tests](#lancer-les-tests)
  - [Structure du projet](#structure-du-projet)
  - [Algorithmes](#algorithmes)
    - [Störmer-Verlet](#störmer-verlet)
    - [Potentiel de Lennard-Jones](#potentiel-de-lennard-jones)
    - [Potentiel de paroi — mur bas (`forceMurBas`)](#potentiel-de-paroi--mur-bas-forcemurbas)
    - [Thermostat](#thermostat)
    - [Optimisation — grille de cellules](#optimisation--grille-de-cellules)
  - [Paramètres](#paramètres)
    - [Simulation principale — collision (lab6a)](#simulation-principale--collision-lab6a)
  - [Conditions aux limites](#conditions-aux-limites)
  - [Gestion des erreurs](#gestion-des-erreurs)
    - [Vérifications en place](#vérifications-en-place)
  - [Tests](#tests)
  - [Visualisation](#visualisation)
  - [Documentation](#documentation)

---

## Compilation et exécution

### Compiler

```bash
mkdir  build 
cd build
cmake ..
make 
```

### Lancer la simulation

```bash
# depuis build/
./demo/simulation
```

Affichage de la progression :
```
Nombre de particules : 17622
t = 0.5
t = 1.0
...
Simulation terminee !
```

### Lancer les tests

```bash
ctest -V                                      # tous les tests
```

---

## Structure du projet

```
TP_jmeilim_lehbibm/
├── include/
│   ├── Particle.hxx          # position, vitesse, masse, cat, isAlive
│   ├── Vector.hxx            # vecteur 3D avec opérateurs surchargés
│   ├── Cellule.hxx           # cellule de la grille (center + indices)
│   ├── Univers.hxx           # domaine, grille, liste de particules
│   ├── Forces.hxx            # computeForce, computeGravity, forceMurBas
│   ├── Stromer.hxx           # algorithme de Störmer-Verlet
│   ├── Boundary.hxx          # conditions aux limites
│   └── GenereException.hxx   # gestion d'erreurs + checkNaN
├── src/
│   ├── Particle.cxx
│   ├── Vector.cxx
│   ├── Univers.cxx
│   ├── Forces.cxx
│   ├── Stromer.cxx
│   ├── Boundary.cxx
│   └── CMakeLists.txt
├── demo/
│   ├── main.cxx              # initialisation + boucle principale
│   └── CMakeLists.txt
├── test/
│   ├── absorption.cxx
│   ├── Climites.cxx
│   ├── Forces.cxx
│   ├── periodique.cxx
│   ├── reflexion.cxx
│   ├── Stromer.cxx
│   ├── Univers.cxx
│   └── CMakeLists.txt
├── doc/
├── CMakeLists.txt
├── Doxyfile
└── README.md
```

---

## Algorithmes

### Störmer-Verlet

Intégration temporelle à chaque itération `dt` :

```
1.  x_i  += dt · v_i  +  0.5 · dt² · F_i / m_i
2.  conditionLimites(p, Lx, Ly)
3.  updateCells()
4.  F_new  =  computeForce()     ← LJ + mur bas + gravité
5.  v_i  += 0.5 · dt · (F_old + F_new) / m_i
6.  F_old  =  F_new
7.  [iter % 1000 = 0]  →  v_i *= β   (thermostat, "rect" uniquement)
```

### Potentiel de Lennard-Jones

```
U(r)  =  4ε [ (σ/r)¹²  −  (σ/r)⁶ ]

F_ij  =  24ε/r²  ·  (σ/r)⁶  ·  (1 − 2(σ/r)⁶)  ·  r_ij
```

### Potentiel de paroi — mur bas (`forceMurBas`)

```
F_i   =  −24ε · (1/2r) · (σ/2r)⁶ · (1 − 2(σ/2r)⁶)
rcut  =  2^(1/6) · σ
```
Appliqué uniquement aux particules `"rect"` proches du bord bas.

### Thermostat

```
Ec        =  Σ  0.5 · m_i · |v_i|²       (sur "rect" uniquement)
Ec_target =  0.005 · N_rect
β         =  √(Ec_target / Ec)
v_i      *=  β                             (toutes les 1000 itérations)
```

### Optimisation — grille de cellules

```
nc_d  =  floor(L_d / rc)
```

Chaque particule n'interagit qu'avec les **9 cellules voisines** (2D),
ce qui réduit la complexité de **O(N²)** à **O(N)**.

---

## Paramètres

### Simulation principale — collision (lab6a)

| Paramètre | Valeur | Description |
|-----------|--------|-------------|
| `Lx` | 250 | longueur domaine en x |
| `Ly` | 180 | longueur domaine en y |
| `ε` | 1.0 | profondeur potentiel LJ |
| `σ` | 1.0 | distance interaction LJ |
| `rc` | 2.5σ | rayon de coupure |
| `dt` | 0.0005 | pas de temps |
| `t_max` | 29.5 | temps final |
| `G` | −12 | intensité gravité |
| `N_rect` | ~17227 | particules rectangle |
| `N_disk` | ~395 | particules disque |
| `Ec_target` | 0.005 × N_rect | énergie cinétique cible |
| `β` | √(Ec_target / Ec) | coefficient thermostat |

Distance inter-particules : `d = 2^(1/6) × σ ≈ 1.122`

---

## Conditions aux limites

| Fonction | Comportement |
|----------|-------------|
| `conditionLimites(p, Lx, Ly)` | réflexion gauche/droite/bas · absorption haut |
| `reflexion(p, Lx, Ly)` | réflexion sur les 4 bords |
| `absorption(p, Lx, Ly)` | absorption sur les 4 bords |
| `periodique(p, Lx, Ly)` | téléportation sur les 4 bords |

Réflexion : inversion de la composante de vitesse perpendiculaire au bord.  
Absorption : `setAlive(false)` — la particule est exclue des calculs suivants.  
Périodique : `pos += L` ou `pos -= L` sans modification de la vitesse.

---

## Gestion des erreurs

Le projet utilise `GenereException` (hérite de `std::runtime_error`) :

```cpp
class GenereException : public std::runtime_error {
public:
    explicit GenereException(const std::string& msg)
        : std::runtime_error("[Erreur] " + msg) {}
};


```

### Vérifications en place

| Où | Ce qui est vérifié |
|----|-------------------|
| `Univers()` | `rc > 0`, `lx > 0`, `ly > 0` |
| `stromer()` | `dt > 0` |
| `stromer()` | `Ec > 0` avant calcul de β |
| `stromer()` | NaN/inf sur positions et vitesses |
| `main()` | `try/catch` global |

Exemple de messages :
```
[Erreur] rc doit être > 0
[Erreur] vitesse x particule 42 est NaN ou inf
[Erreur] Energie cinétique nulle, β impossible
```

---

## Tests

46 tests unitaires avec **GoogleTest** (téléchargé automatiquement par CMake).

| Fichier | Groupe | Tests | Ce qui est vérifié |
|---------|--------|-------|--------------------|
| `absorption.cxx` | `AbsorptionTest` | 6 | absorption sur les 4 bords + intérieur vivant |
| `reflexion.cxx` | `ReflexionTest` | 6 | rebond sur les 4 bords + coin + intérieur inchangé |
| `periodique.cxx` | `PeriodiqueTest` | 6 | téléportation sur les 4 bords + coin + intérieur |
| `Climites.cxx` | `ConditionLimitesTest` | 6 | comportement global de `conditionLimites` |
| `Forces.cxx` | `ForcesTest` | 9 | force nulle seul · répulsive · symétrie · gravité |
| `Stromer.cxx` | `StromerTest` | 6 | NaN · déplacement · énergie · thermostat · absorption |
| `Univers.cxx` | `UniversTest` | 7 | constructeur · grille · addParticle · hors domaine |
| | **Total** | **46** | |

---

## Visualisation

Les fichiers `.vtk` sont générés dans `demo/` toutes les 100 itérations.

```bash
# ouvrir dans ParaView
File > Open > demo/out.vtk.series
```

Coloration par type de particule :
- `0` → rectangle (bleu)
- `1` → disque (rouge)

---

## Documentation

```bash
# générer depuis build/
make doc

# ouvrir dans le navigateur
xdg-open ../doc/html/index.html
```