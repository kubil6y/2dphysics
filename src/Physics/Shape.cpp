#include "Shape.h"

CircleShape::CircleShape(float radius) : radius{radius} {
}

CircleShape::~CircleShape() {
}

ShapeType CircleShape::GetType() const {
    return ShapeType::Circle;
}

float CircleShape::GetMomentOfIntertia() const {
    return 0.f;
}

PolygonShape::~PolygonShape() {
}

ShapeType PolygonShape::GetType() const {
    return ShapeType::Polygon;
}

float PolygonShape::GetMomentOfIntertia() const {
    return 0.f;
}

BoxShape::BoxShape(float width, float height) : width{width}, height{height} {
}

BoxShape::~BoxShape() {
}

ShapeType BoxShape::GetType() const {
    return ShapeType::Box;
}

float BoxShape::GetMomentOfIntertia() const {
    return 0.f;
}
