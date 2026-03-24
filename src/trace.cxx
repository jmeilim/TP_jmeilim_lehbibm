/// Code élémentaire pour le calcul de la trace d'une matrice.
/// Printemps 2026
/// Objectif : manipuler les éléments de base du C++
///            utiliser des outils de profiling et de débogage
/// ref: l'exercice est inspiré très largement de ressources WWW

#include <cmath>
#include <cstdlib>
#include <iostream>

double **initialization(int);
double *fill_vectors(double *, int);
void print_matrix(double **, int);
double trace(double **, int);
using std::cout;

/// Driver principal pour le calcul de la tace d'une matrice
int main() {
  int i, j, n , h ;
  double **matrix;
  double sum;
  cout << std::endl << "Enter the step of discretisation : " << std::flush;
  std::cin >> h;
  

  cout << std::endl << "Enter the Dimension for a square matrix: " << std::flush;
  std::cin >> n;
  matrix = initialization(n);
  for (i = 1; i < n; i++)
    matrix[i] = fill_vectors(matrix[i], n);
  sum = trace(matrix, n);
  print_matrix(matrix, n);
  cout << std::endl << "Sum of the diagonal elements are: " << sum;
  return 0;
}

/// @brief Routine d'initialization qui permet d'allouer la mémoire pour une
///        matrice carrée de taille n et renvoie un pointer vers
///        la matrice allouée
/// @param[in] n est la taille souhaitée de la matrice
/// @return    Renvoie le pointeur vers la matrice allouée
double **initialization(int n) {
  int i;
  double **matrix;
  matrix = ( double ** )calloc(n, sizeof(double *));
  for (i = 0; i < n; ++i)
    matrix[i] = ( double *)calloc(n, sizeof(double ));
  return (matrix);
}

/// @brief Intitialise un vecteur avec des valeurs aléatoires comprises
///        entre dans l'intervalle [-10;10]
/// @param[in] vec est le vecteur à initialiser
/// @param[in] n   est la taille du vecteur à initialiser

/// @return    Renvoie le vecteur initialisé.
double *fill_vectors(double *vec, int n) {
  int i;
  for (i = 0; i < n; i++)
    vec[i] = rand() % 20 - 10;
  return vec;
}

/// @brief Affiche les éléments d'une matrice de taille n
/// @param[in] matrix est la matrice à afficher
/// @param[in] n est la taille de la matrice à afficher
void print_matrix(double **matrix, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      cout << matrix[i][j] << ", ";
    cout << std::endl;
  }
}

/// @brief Calcul la trace d'une matrice
/// @param[in] matrix est la matrice dont on souhaite connaître la trace.
/// @param[in] n est la taille de la matrice.
double trace(double **matrix, int n) {
  int i;
  double sum = 0.0;
  for (i = 1; i < n; i++)
    sum += matrix[i][i];
  return sum;
}


double f(double t, double y) {
    return -50.0 * (y - cos(t));
}
/// @brief Résout une EDO par la méthode d’Euler explicite
/// @param[in] h pas de discrétisation
/// @param[in] N nombre d’itérations
/// @return vecteur contenant les approximations de la solution
std::vector<double> euler_explicit(double h, int N) {
    std::vector<double> y(N+1);
    y[0] = 0.0;
    for (int n = 0; n < N; n++) {
        double t = n * h;
        y[n+1] = y[n] + h * f(t, y[n]);
    }
    return y;
}

/// @brief Résout une EDO par la méthode d’Euler implicite
/// @param[in] h pas de discrétisation
/// @param[in] N nombre d’itérations
/// @return vecteur contenant les approximations de la solution
std::vector<double> euler_implicit(double h, int N) {
    std::vector<double> y(N+1);
    y[0] = 0.0;
    for (int n = 0; n < N; n++) {
        double t = (n+1) * h;
        double yn = y[n];
        double ynew = yn;
        for (int k = 0; k < 5; k++) {
            ynew = yn + h * (-50.0 * (ynew - cos(t)));
        }
        y[n+1] = ynew;
    }
    return y;
}