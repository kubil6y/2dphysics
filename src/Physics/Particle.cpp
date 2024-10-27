#include "Particle.h"
#include <iostream>

Particle::Particle(float x, float y, float mass)
    : position{Vec2{x, y}}, mass{mass} {
    std::cout << "Particle constructor called!" << std::endl;
}

Particle::~Particle() {
    std::cout << "Particle destructor called!" << std::endl;
}

void Particle::Integrate(float deltaTime) {
    // Find the acceleration based on the forces
    // that are being applied and the mass
    acceleration = sumForces / mass;

    // Explicit Euler integration for updating position and
    // velocity using current acceleration
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    ClearForces();
}

void Particle::AddForce(const Vec2& force) {
    sumForces += force;
}

void Particle::ClearForces() {
    sumForces *= 0;
}
