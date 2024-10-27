#pragma once

#include "Graphics.h"
#include "Physics/Particle.h"
#include <vector>

class Application {
private:
    bool running = false;

    std::vector<Particle*> particles;
    Vec2 pushForce = {0.f, 0.f};

public:
    Application() = default;
    ~Application() = default;

    bool IsRunning();
    void Setup();
    void Input();
    void Update();
    void Render();
    void Destroy();
};
