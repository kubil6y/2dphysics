#include "Body.h"
#include <cmath>
#include <iostream>

Body::Body(const Shape& shape, float x, float y, float m) {
    this->shape = shape.Clone();
    position = Vec2{x, y};
    velocity = Vec2{0.f, 0.f};
    acceleration = Vec2{0.f, 0.f};
    rotation = 0.f;
    angularVelocity = 0.f;
    angularAcceleration = 0.f;
    sumForces = Vec2{0.f, 0.f};
    sumTorque = 0.f;

    this->mass = m;
    if (mass != 0) {
        invMass = 1.f / mass;
    } else {
        // Infinite mass (static object)
        invMass = 0.f;
    };

    I = shape.GetMomentOfInertia(mass);
    if (I != 0.f) {
        invI = 1.f / I;
    } else {
        invI = 0.f;
    };

    std::cout << "Body constructor called!" << std::endl;
}

Body::~Body() {
    delete shape;
    std::cout << "Body destructor called!" << std::endl;
}

bool Body::IsStatic() const {
    float epsilon = 1e-6;
    return fabs(invMass - 0.f) < epsilon;
}

void Body::Update(float dt) {
    if (IsStatic()) {
        return;
    }

    IntegrateLinear(dt);
    IntegrateAngular(dt);

    bool isPolygon = shape->GetType() == ShapeType::Polygon ||
                     shape->GetType() == ShapeType::Box;
    if (isPolygon) {
        PolygonShape* polygonShape = static_cast<PolygonShape*>(shape);
        polygonShape->UpdateVertices(rotation, position);
    }
}

void Body::IntegrateLinear(float dt) {
    // Find the acceleration based on the forces
    // that are being applied and the mass
    acceleration = sumForces * invMass; // a = F/m
    // Explicit Euler integration for updating position and
    // velocity using current acceleration
    velocity += acceleration * dt;
    position += velocity * dt;
    ClearForces();
}

void Body::IntegrateAngular(float dt) {
    angularAcceleration = sumTorque * invI;
    angularVelocity += angularAcceleration * dt;
    rotation += angularVelocity * dt;
    ClearTorque();
}

void Body::AddForce(const Vec2& force) {
    sumForces += force;
}

void Body::ClearForces() {
    sumForces *= 0.f;
}

void Body::AddTorque(float torque) {
    sumTorque += torque;
}

void Body::ClearTorque() {
    sumTorque = 0.f;
}

// Impulse is an instantaneous change in velocity,
// inversely proportional to the mass of the object.
// Momentum P=m*V
// Impulse J the change in momentum: J = ΔP = m * ΔV
// Therefore, the change in velocity is: ΔV = J / m
void Body::ApplyImpulse(const Vec2& j) {
    if (IsStatic()) {
        return;
    }
    velocity += j * invMass;
}
