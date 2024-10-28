#pragma once

#include "Graphics.h"
#include "Physics/Body.h"
#include <SDL.h>
#include <vector>

class Application {
public:
    Application() = default;
    ~Application() = default;

    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();

private:
    bool running = false;

    Vec2 pushForce = {0.f, 0.f};
    Vec2 mouseCursor = {0.f, 0.f};
    bool leftMouseButtonDown = false;
    std::vector<Body*> bodies;

    float springK = 1500.f;
    float restLength = 200.f;
    const int NUM_BODIES = 4;
};
