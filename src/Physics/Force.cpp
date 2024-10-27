#include "Force.h"

Vec2 Force::GenerateDragForce(const Particle& particle, float k) {
    Vec2 dragForce;
    if (particle.velocity.MagnitudeSquared() > 0.f) {
        Vec2 dragDir = particle.velocity.Normalized() * -1.f;
        float dragMagnitude = k * particle.velocity.MagnitudeSquared();
        dragForce = dragDir * dragMagnitude;
    }
    return dragForce;
}