#pragma once

#include "Shape.h"
#include "Vec2.h"

struct Body {
    // Linear motion
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;
    // Angular motion
    float rotation;
    float angularVelocity;
    float angularAcceleration;

    Vec2 sumForces;
    float sumTorque;

    float mass;
    float invMass;

    float I;
    float invI;

    Shape* shape = nullptr;

    Body(const Shape& shape, float x, float y, float m);
    ~Body();

    void Integrate(float dt);
    void IntegrateLinear(float dt);
    void IntegrateAngular(float dt);
    void AddForce(const Vec2& force);
    void ClearForces();
    void AddTorque(float torque);
    void ClearTorque();
};
