#pragma once

#include "Graphics.h"
#include "Physics/Particle.h"
#include <vector>

class Application {
private:
    bool running = false;
    Particle* particle;
    std::vector<Particle*> particles;

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
