#pragma once

#include "Body.h"
#include "Vec2.h"

struct Contact {
    Body* a;
    Body* b;

    Vec2 start;
    Vec2 end;
    Vec2 normal;
    float depth;

    void ResolvePenetration();
};
