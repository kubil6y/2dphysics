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
    virtual float GetMomentOfIntertia() const = 0;
};

struct CircleShape : public Shape {
    float radius;

    CircleShape(float radius);
    virtual ~CircleShape();

    ShapeType GetType() const override;
    float GetMomentOfIntertia() const override;
};

struct PolygonShape : public Shape {
    std::vector<Vec2> vertices;

    PolygonShape(const std::vector<Vec2>& vertices);
    virtual ~PolygonShape();

    ShapeType GetType() const override;
    float GetMomentOfIntertia() const override;
};

struct BoxShape : public Shape {
    float width;
    float height;

    BoxShape(float width, float height);
    virtual ~BoxShape();

    ShapeType GetType() const override;
    float GetMomentOfIntertia() const override;
};
