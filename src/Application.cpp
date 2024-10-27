#include "Application.h"
#include "Physics/Constants.h"
#include "Physics/Force.h"
#include "Physics/Particle.h"

bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();

    Particle* smallBall = new Particle(50, 100, 1.f);
    smallBall->radius = 4;
    particles.push_back(smallBall);

    Particle* bigBall = new Particle(150, 100, 3.f);
    bigBall->radius = 12;
    particles.push_back(bigBall);

    liquid.x = 0.f;
    liquid.y = Graphics::Height() / 2.f;
    liquid.w = Graphics::Width();
    liquid.h = Graphics::Height();
}

void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                running = false;
            };
            if (event.key.keysym.sym == SDLK_w) {
                pushForce.y = -50 * PIXELS_PER_METER;
            }
            if (event.key.keysym.sym == SDLK_s) {
                pushForce.y = 50 * PIXELS_PER_METER;
            }
            if (event.key.keysym.sym == SDLK_d) {
                pushForce.x = 50 * PIXELS_PER_METER;
            }
            if (event.key.keysym.sym == SDLK_a) {
                pushForce.x = -50 * PIXELS_PER_METER;
            }
            break;

        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_w) {
                pushForce.y = 0.f;
            }
            if (event.key.keysym.sym == SDLK_s) {
                pushForce.y = 0.f;
            }
            if (event.key.keysym.sym == SDLK_d) {
                pushForce.x = 0.f;
            }
            if (event.key.keysym.sym == SDLK_a) {
                pushForce.x = 0.f;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                int x = 0.f;
                int y = 0.f;
                SDL_GetMouseState(&x, &y);
                Particle* p = new Particle(x, y, 1.f);
                p->radius = 4.f;
                particles.push_back(p);
            }
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
    if (deltaTime > 0.016f) {
        deltaTime = 0.016f;
    }
    timePreviousFrame = SDL_GetTicks();

    // Apply forces to particles
    for (auto particle : particles) {
        Vec2 weight{0.f, particle->mass * 9.81f * PIXELS_PER_METER};
        particle->AddForce(weight);
        particle->AddForce(pushForce);

        if (particle->position.y >= liquid.y) {
            float dragK = 0.03f;
            Vec2 drag = Force::GenerateDragForce(*particle, dragK);
            particle->AddForce(drag);
        }
    }

    // Integrate the acceleration and velocity to estimate new position
    for (auto particle : particles) {
        particle->Integrate(deltaTime);
    }

    // Bounds correction
    for (auto particle : particles) {
        if (particle->position.x - particle->radius <= 0) {
            particle->position.x = particle->radius;
            particle->velocity.x *= -0.9;
        } else if (particle->position.x + particle->radius >=
                   Graphics::Width()) {
            particle->position.x = Graphics::Width() - particle->radius;
            particle->velocity.x *= -0.9;
        }
        if (particle->position.y - particle->radius <= 0) {
            particle->position.y = particle->radius;
            particle->velocity.y *= -0.9;
        } else if (particle->position.y + particle->radius >=
                   Graphics::Height()) {
            particle->position.y = Graphics::Height() - particle->radius;
            particle->velocity.y *= -0.9;
        }
    }
}

void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    // Draw liquid
    Graphics::DrawFillRect(liquid.x + liquid.w / 2.f, liquid.y + liquid.h / 2.f,
                           liquid.w, liquid.h, 0XFF6E1713);

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
