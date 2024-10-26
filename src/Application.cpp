#include "Application.h"
#include "Physics/Constants.h"

bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();

    particle = new Particle(50, 100, 1.f);
    particle->acceleration = Vec2{0.f, 9.81f * PIXELS_PER_METER};
    particle->velocity = Vec2{500.f, 200.f};
    particle->radius = 4;
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

    // Integration of velocity and acceleration
    particle->velocity += particle->acceleration * deltaTime;
    particle->position += particle->velocity * deltaTime;

    // Keep in boundaries
    if (particle->position.x >= Graphics::Width() || particle->position.x <= 0.f) {
        particle->velocity.x *= -1;
    }
    if (particle->position.y >= Graphics::Height() || particle->position.y <= 0.f) {
        particle->velocity.y *= -1;
    }
}

void Application::Render() {
    Graphics::ClearScreen(0xFF056263);
    Graphics::DrawFillCircle(particle->position.x, particle->position.y, particle->radius,
                             0xFFFFFFFF);
    Graphics::RenderFrame();
}

void Application::Destroy() {
    delete particle;
    Graphics::CloseWindow();
}
