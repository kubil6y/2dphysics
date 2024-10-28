#pragma once

#include "Body.h"
#include "Vec2.h"

class Force {
public:
    static Vec2 GenerateDragForce(const Body& particle, float k);
    static Vec2 GenerateFrictionForce(const Body& particle, float k);
    static Vec2 GenerateGravitationalForce(const Body& a, const Body& b,
                                           float G, float minDistanceSqr,
                                           float maxDistanceSqr);
    static Vec2 GenerateSpringForce(const Body& particle, Vec2 anchor,
                                    float restLength, float k);
    static Vec2 GenerateSpringForce(const Body& a, const Body& b,
                                    float restLength, float k);
};
