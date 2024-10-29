#pragma once

#include "Vec2.h"
#include <vector>

enum class ShapeType {
    Box,
    Circle,
    Polygon,
};

struct Shape {
    virtual ~Shape() = default;
    virtual ShapeType GetType() const = 0;
    // Without mass (Body will handle the mass)
    virtual float GetMomentOfInertia(float mass) const = 0; 
    virtual Shape* Clone() const = 0;
};

struct CircleShape : public Shape {
    float radius;

    CircleShape(float radius);
    virtual ~CircleShape();

    ShapeType GetType() const override;
    float GetMomentOfInertia(float mass) const override;
    Shape* Clone() const override;
};

struct PolygonShape : public Shape {
    std::vector<Vec2> vertices;

    PolygonShape() = default;
    PolygonShape(const std::vector<Vec2> vertices);
    virtual ~PolygonShape();

    ShapeType GetType() const override;
    float GetMomentOfInertia(float mass) const override;
    Shape* Clone() const override;
};

struct BoxShape : public Shape {
    float width;
    float height;

    BoxShape() = default;
    BoxShape(float width, float height);
    virtual ~BoxShape();

    ShapeType GetType() const override;
    float GetMomentOfInertia(float mass) const override;
    Shape* Clone() const override;
};
