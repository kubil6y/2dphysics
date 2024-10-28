#include "Body.h"
#include <iostream>

Body::Body(float x, float y, float mass) : position{Vec2{x, y}}, mass{mass} {
    if (mass != 0) {
        invMass = 1.f / mass;
    }
    std::cout << "Body constructor called!" << std::endl;
}

Body::~Body() {
    std::cout << "Body destructor called!" << std::endl;
}

void Body::Integrate(float deltaTime) {
    // Find the acceleration based on the forces
    // that are being applied and the mass
    acceleration = sumForces * invMass; // a = F/m

    // Explicit Euler integration for updating position and
    // velocity using current acceleration
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;

    ClearForces();
}

void Body::AddForce(const Vec2& force) {
    sumForces += force;
}

void Body::ClearForces() {
    sumForces *= 0;
}

void Body::SetMass(float mass) {
    this->mass = mass;
    if (mass != 0) {
        invMass = 1.f / mass;
    }
}
