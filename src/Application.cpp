#include "Application.h"
#include "Physics/Constants.h"
#include "Physics/Force.h"
#include "Physics/Particle.h"

bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();

    Particle* a = new Particle(100.f, 100.f, 1.f);
    Particle* b = new Particle(300.f, 100.f, 1.f);
    Particle* c = new Particle(300.f, 300.f, 1.f);
    Particle* d = new Particle(100.f, 300.f, 1.f);

    a->radius = 6.f;
    b->radius = 6.f;
    c->radius = 6.f;
    d->radius = 6.f;

    particles.push_back(a);
    particles.push_back(b);
    particles.push_back(c);
    particles.push_back(d);
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
                int lastParticle = NUM_PARTICLES - 1;
                Vec2 impulseDir =
                    (particles[lastParticle]->position - mouseCursor)
                        .Normalized();
                float impulseMagnitude =
                    (particles[lastParticle]->position - mouseCursor)
                        .Magnitude() *
                    5.f;
                particles[lastParticle]->velocity =
                    impulseDir * impulseMagnitude;
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

        Vec2 drag = Force::GenerateDragForce(*particle, .003f);
        particle->AddForce(drag);

        Vec2 weight = {0.f, particle->mass * 9.81f * PIXELS_PER_METER};
        particle->AddForce(weight);
    }

    // clang-format off
    Vec2 ab = Force::GenerateSpringForce(*particles[0], *particles[1], restLength, springK);
    particles[0]->AddForce(ab);
    particles[1]->AddForce(-ab);

    Vec2 bc = Force::GenerateSpringForce(*particles[1], *particles[2], restLength, springK);
    particles[1]->AddForce(bc);
    particles[2]->AddForce(-bc);

    Vec2 cd = Force::GenerateSpringForce(*particles[2], *particles[3], restLength, springK);
    particles[2]->AddForce(cd);
    particles[3]->AddForce(-cd);

    Vec2 da = Force::GenerateSpringForce(*particles[3], *particles[0], restLength, springK);
    particles[3]->AddForce(da);
    particles[0]->AddForce(-da);

    Vec2 ac = Force::GenerateSpringForce(*particles[0], *particles[2], restLength, springK);
    particles[0]->AddForce(ac);
    particles[2]->AddForce(-ac);

    Vec2 bd = Force::GenerateSpringForce(*particles[1], *particles[3], restLength, springK);
    particles[1]->AddForce(bd);
    particles[3]->AddForce(-bd);
    // clang-format on

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
    if (leftMouseButtonDown) {
        int lastParticle = NUM_PARTICLES - 1;
        Graphics::DrawLine(particles[lastParticle]->position.x,
                           particles[lastParticle]->position.y, mouseCursor.x,
                           mouseCursor.y, 0xFF313131);
    }

    // clang-format off
    Graphics::DrawLine(particles[0]->position.x, particles[0]->position.y,particles[1]->position.x,particles[1]->position.y, 0xFF313131);
    Graphics::DrawLine(particles[1]->position.x, particles[1]->position.y,particles[2]->position.x,particles[2]->position.y, 0xFF313131);
    Graphics::DrawLine(particles[2]->position.x, particles[2]->position.y,particles[3]->position.x,particles[3]->position.y, 0xFF313131);
    Graphics::DrawLine(particles[3]->position.x, particles[3]->position.y,particles[0]->position.x,particles[0]->position.y, 0xFF313131);
    Graphics::DrawLine(particles[0]->position.x, particles[0]->position.y,particles[2]->position.x,particles[2]->position.y, 0xFF313131);
    Graphics::DrawLine(particles[1]->position.x, particles[1]->position.y,particles[3]->position.x,particles[3]->position.y, 0xFF313131);
    // clang-format on

    for (auto particle : particles) {
        Graphics::DrawFillCircle(particle->position.x, particle->position.y,
                                 particle->radius, 0XFFEEBB00);
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
