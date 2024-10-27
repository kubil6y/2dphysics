#include "Force.h"

Vec2 Force::GenerateDragForce(const Particle& particle, float k) {
    Vec2 dragForce;
    if (particle.velocity.MagnitudeSqr() > 0.f) {
        Vec2 dragDir = particle.velocity.Normalized() * -1.f;
        float dragMagnitude = k * particle.velocity.MagnitudeSqr();
        dragForce = dragDir * dragMagnitude;
    }
    return dragForce;
}

Vec2 Force::GenerateFrictionForce(const Particle& particle, float k) {
    Vec2 frictionForce;
    if (particle.velocity.MagnitudeSqr() > 0.f) {
        Vec2 frictionDir = particle.velocity.Normalized() * -1.f;
        frictionForce = frictionDir * k;
    }
    return frictionForce;
}

Vec2 Force::GenerateGravitationalForce(const Particle& a, const Particle& b,
                                       float G) {
    Vec2 distance = b.position - a.position;
    float distanceSqr = distance.MagnitudeSqr();
    Vec2 distanceDir = distance.Normalized();
    float attractionMagnitude = G * (a.mass * b.mass) / distanceSqr;
    Vec2 attractionForce = distanceDir * attractionMagnitude;
    return attractionForce;
}
