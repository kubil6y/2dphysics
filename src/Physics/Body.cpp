#include "Body.h"
#include <iostream>

Body::Body(const Shape& shape, float x, float y, float m)
    : position{Vec2{x, y}}, mass{m} {
    // take reference to copy so we can use stack values
    // in constuctor ex: new Body(CircleShape()...)
    this->shape = shape.Clone();

    if (mass != 0) {
        invMass = 1.f / mass;
    }
    std::cout << "Body constructor called!" << std::endl;
}

Body::~Body() {
    delete shape;
    std::cout << "Body destructor called!" << std::endl;
}

void Body::Integrate(float dt) {
    // Find the acceleration based on the forces
    // that are being applied and the mass
    acceleration = sumForces * invMass; // a = F/m

    // Explicit Euler integration for updating position and
    // velocity using current acceleration
    velocity += acceleration * dt;
    position += velocity * dt;

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
