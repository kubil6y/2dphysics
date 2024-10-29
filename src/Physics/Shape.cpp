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

float CircleShape::GetMomentOfInertia(float mass) const {
    // I = 1/2 * r^2 * mass
    return .5f * radius * radius * mass;
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

float PolygonShape::GetMomentOfInertia(float mass) const {
    // TODO:
    return 0.f;
}

Shape* PolygonShape::Clone() const {
    return new PolygonShape{vertices};
}

BoxShape::BoxShape(float width, float height) {
    this->width = width;
    this->height = height;

    // Center of mass is in the middle
    // Load vertices of the box polygon clockwise
    vertices.push_back(Vec2{-width / 2.f, -height / 2.f});
    vertices.push_back(Vec2{width / 2.f, -height / 2.f});
    vertices.push_back(Vec2{width / 2.f, height / 2.f});
    vertices.push_back(Vec2{-width / 2.f, height / 2.f});
    std::cout << "BoxShape constructor called" << std::endl;
}

BoxShape::~BoxShape() {
    std::cout << "BoxShape destructor called" << std::endl;
}

ShapeType BoxShape::GetType() const {
    return ShapeType::Box;
}

float BoxShape::GetMomentOfInertia(float mass) const {
    // I = 1/12 * (w^2 * h^2) * mass
    return 0.08333 * (width * width * height * height) * mass;
}

Shape* BoxShape::Clone() const {
    return new BoxShape{width, height};
}
