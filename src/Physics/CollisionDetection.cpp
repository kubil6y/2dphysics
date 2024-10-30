#include "CollisionDetection.h"
#include "Shape.h"

bool CollisionDetection::IsColliding(Body* a, Body* b) {
    if (Shape::IsCircle(a) && Shape::IsCircle(b)) {
        return IsCollidingCircleCircle(a, b);
    }
    if (Shape::IsCircle(a) && Shape::IsPolygon(b)) {
        return IsCollidingPolygonCircle(b, a);
    }
    if (Shape::IsCircle(b) && Shape::IsPolygon(a)) {
        return IsCollidingPolygonCircle(a, b);
    }
    if (Shape::IsPolygon(a) && Shape::IsPolygon(b)) {
        return IsCollidingPolygonPolygon(a, b);
    }
    // TODO: Handle other types
    return false;
}

bool CollisionDetection::IsCollidingCircleCircle(Body* a, Body* b) {
    CircleShape* aShape = static_cast<CircleShape*>(a->shape);
    CircleShape* bShape = static_cast<CircleShape*>(b->shape);
    float distanceSqr = (a->position - b->position).MagnitudeSqr();
    float sumRadius = aShape->radius + bShape->radius;
    return distanceSqr <= (sumRadius * sumRadius);
}

bool CollisionDetection::IsCollidingPolygonPolygon(Body* a, Body* b) {
    return false;
}

bool CollisionDetection::IsCollidingPolygonCircle(Body* p, Body* c) {
    CircleShape* cricleShape = static_cast<CircleShape*>(c->shape);
    PolygonShape* polygonShape = static_cast<PolygonShape*>(p->shape);
    return false;
}
