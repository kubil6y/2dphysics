#include "Application.h"
#include "Physics/Constants.h"

bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();

    Particle* smallBall = new Particle(50, 100, 1.f);
    smallBall->radius = 4;
    particles.push_back(smallBall);

    Particle* bigBall = new Particle(50, 200, 3.f);
    bigBall->radius = 12;
    particles.push_back(bigBall);
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

    // Apply wind force
    Vec2 wind{0.2f * PIXELS_PER_METER, 0.f};
    for (auto particle : particles) {
        particle->AddForce(wind);
    }

    for (auto particle : particles) {
        particle->Integrate(deltaTime);
    }

    for (auto particle : particles) {
        // Keep in boundaries
        if (particle->position.x - particle->radius <= 0) {
            particle->position.x = particle->radius;
            particle->velocity.x *= -0.9f;
        } else if (particle->position.x + particle->radius >=
                   Graphics::Width()) {
            particle->position.x = Graphics::Width() - particle->radius;
            particle->velocity.x *= -0.9f;
        } else if (particle->position.y - particle->radius <= 0) {
            particle->position.y = particle->radius;
            particle->velocity.y *= -0.9f;
        } else if (particle->position.y + particle->radius >=
                   Graphics::Height()) {
            particle->position.y = Graphics::Height() - particle->radius;
            particle->velocity.y *= -0.9f;
        }
    }
}

void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    for (auto particle : particles) {
        Graphics::DrawFillCircle(particle->position.x, particle->position.y,
                                 particle->radius, 0xFFFFFFFF);
    }

    Graphics::RenderFrame();
}

void Application::Destroy() {
    for (auto particle : particles) {
        delete particle;
    }
    particles.clear();

    Graphics::CloseWindow();
}
