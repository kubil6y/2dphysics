#include "Application.h"
#include "Physics/Constants.h"
#include "Physics/Force.h"
#include "Physics/Particle.h"

bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();

    Particle* smallBall = new Particle(200.f, 200.f, 1.f);
    smallBall->radius = 6;
    particles.push_back(smallBall);

    Particle* bigBall = new Particle(500.f, 500.f, 20.f);
    bigBall->radius = 20;
    particles.push_back(bigBall);

    // liquid.x = 0.f;
    // liquid.y = Graphics::Height() / 2.f;
    // liquid.w = Graphics::Width();
    // liquid.h = Graphics::Height();
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
        case SDL_MOUSEMOTION:
            mouseCursor.x = event.motion.x;
            mouseCursor.y = event.motion.y;
        case SDL_MOUSEBUTTONDOWN:
            if (!leftMouseButtonDown &&
                event.button.button == SDL_BUTTON_LEFT) {
                leftMouseButtonDown = true;
                int x, y;
                SDL_GetMouseState(&x, &y);
                mouseCursor.x = x;
                mouseCursor.y = y;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (leftMouseButtonDown && event.button.button == SDL_BUTTON_LEFT) {
                leftMouseButtonDown = false;
                Vec2 impulseDir =
                    (particles[0]->position - mouseCursor).Normalized();
                float impulseMagnitude =
                    (particles[0]->position - mouseCursor).Magnitude() * 5.f;
                particles[0]->velocity = impulseDir * impulseMagnitude;
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
        particle->AddForce(pushForce);
        Vec2 friction = Force::GenerateFrictionForce(*particle, 20.f);
        particle->AddForce(friction);
    }

    // Apply gravitational force to our two planets
    Vec2 attraction =
        Force::GenerateGravitationalForce(*particles[0], *particles[1], 1000.f, 5.f, 100.f);
    printf("%f,%f\n", attraction.x, attraction.y);
    particles[0]->AddForce(attraction);
    particles[1]->AddForce(-attraction);

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
    Graphics::ClearScreen(0xFF0F0721);

    Graphics::DrawFillCircle(particles[0]->position.x, particles[0]->position.y,
                             particles[0]->radius, 0XFFAA3300);
    Graphics::DrawFillCircle(particles[1]->position.x, particles[1]->position.y,
                             particles[1]->radius, 0xFF00FFFF);

    Graphics::RenderFrame();
}

void Application::Destroy() {
    for (auto particle : particles) {
        delete particle;
    }
    particles.clear();

    Graphics::CloseWindow();
}
