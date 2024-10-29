#include "Application.h"
#include "Physics/Body.h"
#include "Physics/Constants.h"
#include "Physics/Force.h"

bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();

    Body* body = new Body{CircleShape{50.f}, 100.f, 100.f, 1.f};
    bodies.push_back(body);
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
                    (bodies[0]->position - mouseCursor).Normalized();
                float impulseMagnitude =
                    (bodies[0]->position - mouseCursor).Magnitude() * 5.f;
                bodies[0]->velocity = impulseDir * impulseMagnitude;
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

    // Apply forces to bodies
    for (auto body : bodies) {
        body->AddForce(pushForce);

        Vec2 drag = Force::GenerateDragForce(*body, .003f);
        body->AddForce(drag);

        Vec2 weight = {0.f, body->mass * 9.81f * PIXELS_PER_METER};
        body->AddForce(weight);
    }

    // Integrate the acceleration and velocity to estimate new position
    for (auto body : bodies) {
        body->Integrate(deltaTime);
    }

    // Bounds correction
    for (auto body : bodies) {
        if (body->shape->GetType() == ShapeType::Circle) {
            CircleShape* circleShape = static_cast<CircleShape*>(body->shape);
            if (body->position.x - circleShape->radius <= 0) {
                body->position.x = circleShape->radius;
                body->velocity.x *= -0.9;
            } else if (body->position.x + circleShape->radius >=
                       Graphics::Width()) {
                body->position.x = Graphics::Width() - circleShape->radius;
                body->velocity.x *= -0.9;
            }
            if (body->position.y - circleShape->radius <= 0) {
                body->position.y = circleShape->radius;
                body->velocity.y *= -0.9;
            } else if (body->position.y + circleShape->radius >=
                       Graphics::Height()) {
                body->position.y = Graphics::Height() - circleShape->radius;
                body->velocity.y *= -0.9;
            }
        } else {
            // TODO check boundaries of others
        }
    }
}

void Application::Render() {
    Graphics::ClearScreen(0xFF0F0721);

    static float angle = 0.f;

    if (leftMouseButtonDown) {
        Graphics::DrawLine(bodies[0]->position.x, bodies[0]->position.y,
                           mouseCursor.x, mouseCursor.y, 0xFF313131);
    }

    for (auto body : bodies) {
        if (body->shape->GetType() == ShapeType::Circle) {
            CircleShape* circleShape = static_cast<CircleShape*>(body->shape);
            Graphics::DrawCircle(body->position.x, body->position.y,
                                 circleShape->radius, angle, 0XFFFFFFFF);
        } else {
            // TODO draw other types
        }
    }

    angle += 0.01f;

    Graphics::RenderFrame();
}

void Application::Destroy() {
    for (auto body : bodies) {
        delete body;
    }
    bodies.clear();
    Graphics::CloseWindow();
}
