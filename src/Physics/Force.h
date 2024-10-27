#pragma once

#include "Particle.h"
#include "Vec2.h"

class Force {
public:
    static Vec2 GenerateDragForce(const Particle& particle, float k);
};