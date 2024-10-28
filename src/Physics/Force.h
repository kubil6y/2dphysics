#pragma once

#include "Particle.h"
#include "Vec2.h"

class Force {
public:
    static Vec2 GenerateDragForce(const Particle& particle, float k);
    static Vec2 GenerateFrictionForce(const Particle& particle, float k);
    static Vec2 GenerateGravitationalForce(const Particle& a, const Particle& b,
                                       float G, float minDistanceSqr,
                                       float maxDistanceSqr);
};
