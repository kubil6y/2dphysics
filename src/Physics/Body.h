#pragma once

#include "Shape.h"
#include "Vec2.h"

struct Body {
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    // Forces
    Vec2 sumForces;

    // Mass
    float mass;
    float invMass;

    int radius;

    Body(const Shape& shape, float x, float y, float m);
    ~Body();

    void Integrate(float deltaTime);
    void AddForce(const Vec2& force);
    void ClearForces();
    void SetMass(float mass);
};
