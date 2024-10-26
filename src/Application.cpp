#include "Application.h"
#include "Physics/Constants.h"
#include <iostream>
#include <string>

bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();
    particle = new Particle(50, 100, 1.f);
}

void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            break;
        }
    }
}

void Application::Update() {
    static int timePreviousFrame = 0;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0) {
        SDL_Delay(timeToWait);
    }

    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.f;
    if (deltaTime > 0.016) {
        deltaTime = 0.016f;
    }
    timePreviousFrame = SDL_GetTicks();

    std::cout << std::to_string(deltaTime) << std::endl;

    particle->velocity = Vec2(100 * deltaTime, 30 * deltaTime);
    particle->position += particle->velocity;
}

void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(particle->position.x, particle->position.y, 4.f,
                             0xFFFFFFFF);
    Graphics::RenderFrame();
}

void Application::Destroy() {
    delete particle;
    Graphics::CloseWindow();
}
