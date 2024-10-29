#pragma once

#include "Shape.h"
#include "Vec2.h"

struct Body {
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;
    Vec2 sumForces;

    float mass;
    float invMass;

    float rotation;
    float angularVelocity;
    float angularAcceleration;

    Shape* shape = nullptr;

    Body(const Shape& shape, float x, float y, float m);
    ~Body();

    void Integrate(float dt);
    void IntegrateAngular(float dt);
    void AddForce(const Vec2& force);
    void ClearForces();
    void SetMass(float mass);
};
