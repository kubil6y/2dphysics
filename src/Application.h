#pragma once

#include "Graphics.h"
#include "Physics/Particle.h"
#include <vector>
#include <SDL.h>

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

    std::vector<Particle*> particles;
    Vec2 pushForce = {0.f, 0.f};
    Vec2 mouseCursor = {0.f, 0.f};
    bool leftMouseButtonDown = false;

    // TODO: create liquid
    SDL_Rect liquid;
};
