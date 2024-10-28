#include "Force.h"
#include <algorithm>

Vec2 Force::GenerateDragForce(const Body& body, float k) {
    Vec2 dragForce;
    if (body.velocity.MagnitudeSqr() > 0.f) {
        Vec2 dragDir = body.velocity.Normalized() * -1.f;
        float dragMagnitude = k * body.velocity.MagnitudeSqr();
        dragForce = dragDir * dragMagnitude;
    }
    return dragForce;
}

Vec2 Force::GenerateFrictionForce(const Body& body, float k) {
    Vec2 frictionForce;
    if (body.velocity.MagnitudeSqr() > 0.f) {
        Vec2 frictionDir = body.velocity.Normalized() * -1.f;
        frictionForce = frictionDir * k;
    }
    return frictionForce;
}

Vec2 Force::GenerateGravitationalForce(const Body& a, const Body& b, float G,
                                       float minDistanceSqr,
                                       float maxDistanceSqr) {
    Vec2 distance = b.position - a.position;
    float distanceSqr = distance.MagnitudeSqr();
    // Clamping for game dev purposes
    distanceSqr = std::clamp(distanceSqr, minDistanceSqr, maxDistanceSqr);

    Vec2 distanceDir = distance.Normalized();
    float attractionMagnitude = G * (a.mass * b.mass) / distanceSqr;
    Vec2 attractionForce = distanceDir * attractionMagnitude;
    return attractionForce;
}

Vec2 Force::GenerateSpringForce(const Body& body, Vec2 anchor, float restLength,
                                float k) {
    Vec2 toAnchor = body.position - anchor;
    float displacement = toAnchor.Magnitude() - restLength;

    Vec2 springDir = toAnchor.Normalized();
    float springMagnitude = -k * displacement;
    Vec2 springForce = springDir * springMagnitude;
    return springForce;
}

Vec2 Force::GenerateSpringForce(const Body& a, const Body& b, float restLength,
                                float k) {
    Vec2 toAnchor = a.position - b.position;
    float displacement = toAnchor.Magnitude() - restLength;

    Vec2 springDir = toAnchor.Normalized();
    float springMagnitude = -k * displacement;
    Vec2 springForce = springDir * springMagnitude;
    return springForce;
}
