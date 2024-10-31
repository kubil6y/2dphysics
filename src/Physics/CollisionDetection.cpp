#include "CollisionDetection.h"

bool CollisionDetection::IsColliding(Body* a, Body* b, Contact& contact) {
    if (Shape::IsCircle(a) && Shape::IsCircle(b)) {
        return IsCollidingCircleCircle(a, b, contact);
    }
    if (Shape::IsCircle(a) && Shape::IsPolygon(b)) {
        return IsCollidingPolygonCircle(b, a, contact);
    }
    if (Shape::IsCircle(b) && Shape::IsPolygon(a)) {
        return IsCollidingPolygonCircle(a, b, contact);
    }
    if (Shape::IsPolygon(a) && Shape::IsPolygon(b)) {
        return IsCollidingPolygonPolygon(a, b, contact);
    }
    // TODO: Handle other types
    return false;
}

bool CollisionDetection::IsCollidingCircleCircle(Body* a, Body* b,
                                                 Contact& contact) {
    CircleShape* aShape = static_cast<CircleShape*>(a->shape);
    CircleShape* bShape = static_cast<CircleShape*>(b->shape);

    Vec2 ab = b->position - a->position;
    float sumRadius = aShape->radius + bShape->radius;
    float distanceSqr = ab.MagnitudeSqr();
    bool isColliding = distanceSqr <= (sumRadius * sumRadius);
    if (!isColliding) {
        return false;
    }

    contact.a = a;
    contact.b = b;
    contact.normal = ab.Normalized();
    contact.start = b->position - contact.normal * bShape->radius;
    contact.end = a->position + contact.normal * aShape->radius;
    contact.depth = (contact.end - contact.start).Magnitude();

    return true;
}

bool CollisionDetection::IsCollidingPolygonPolygon(Body* a, Body* b,
                                                   Contact& contact) {
    return false;
}

bool CollisionDetection::IsCollidingPolygonCircle(Body* p, Body* c,
                                                  Contact& contact) {
    CircleShape* cricleShape = static_cast<CircleShape*>(c->shape);
    PolygonShape* polygonShape = static_cast<PolygonShape*>(p->shape);
    return false;
}
