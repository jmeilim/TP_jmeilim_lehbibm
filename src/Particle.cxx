#include"../include/Particle.hxx"


/// @brief Accès modifiable position
Vector& Particle::getPosition() { return position; }

/// @brief Accès non modifiable position
const Vector& Particle::getPosition() const { return position; }

/// @brief Accès modifiable vitesse
Vector& Particle::getVitesse() { return vitesse; }

/// @brief Accès non modifiable vitesse
const Vector& Particle::getVitesse() const{
    return vitesse;
}
/// @brief Accès modifiable force
Vector& Particle::getForce() { return force; }

/// @brief Accès non modifiable force
const Vector& Particle::getForce() const{
    return force;
}