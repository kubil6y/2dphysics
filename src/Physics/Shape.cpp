#include "Shape.h"
#include <iostream>

CircleShape::CircleShape(float radius) : radius{radius} {
    std::cout << "CircleShape constructor called" << std::endl;
}

CircleShape::~CircleShape() {
    std::cout << "CircleShape destructor called" << std::endl;
}

ShapeType CircleShape::GetType() const {
    return ShapeType::Circle;
}

float CircleShape::GetMomentOfIntertia() const {
    return 0.f;
}

Shape* CircleShape::Clone() const {
    return new CircleShape{radius};
}

PolygonShape::PolygonShape(const std::vector<Vec2> vertices)
    : vertices{vertices} {
    std::cout << "PolygonShape constructor called" << std::endl;
}

PolygonShape::~PolygonShape() {
    std::cout << "PolygonShape destructor called" << std::endl;
}

ShapeType PolygonShape::GetType() const {
    return ShapeType::Polygon;
}

float PolygonShape::GetMomentOfIntertia() const {
    return 0.f;
}

Shape* PolygonShape::Clone() const {
    return new PolygonShape{vertices};
}

BoxShape::BoxShape(float width, float height) : width{width}, height{height} {
    std::cout << "BoxShape constructor called" << std::endl;
}

BoxShape::~BoxShape() {
    std::cout << "BoxShape destructor called" << std::endl;
}

ShapeType BoxShape::GetType() const {
    return ShapeType::Box;
}

float BoxShape::GetMomentOfIntertia() const {
    return 0.f;
}

Shape* BoxShape::Clone() const {
    return new BoxShape{width, height};
}
