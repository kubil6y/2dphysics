#include "Particle.h"
#include <iostream>

Particle::Particle(float x, float y, float mass)
    : position{Vec2{x, y}}, mass{mass} {
    std::cout << "Particle constructor called!" << std::endl;
}

Particle::~Particle() {
    std::cout << "Particle destructor called!" << std::endl;
}

// Explicit Euler integration for updating position and
// velocity using current acceleration
void Particle::Integrate(float deltaTime) {
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}
