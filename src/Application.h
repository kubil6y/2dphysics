#pragma once

#include "Graphics.h"
#include "Physics/Particle.h"
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
    std::vector<Particle*> particles;

    Vec2 anchor;
    float springK = 300.f;
    float restLength = 15.f;
    const int NUM_PARTICLES = 15;
};
