#include "Application.h"
#include "Physics/Body.h"
#include "Physics/CollisionDetection.h"
#include "Physics/Constants.h"
#include "Physics/Contact.h"
#include <cstdio>

bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();

    Body* bigBall = new Body{CircleShape{200.f}, Graphics::Width() / 2.f,
                             Graphics::Height() / 2.f, 0.f};
    bodies.push_back(bigBall);
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
            break;
        case SDL_MOUSEMOTION:
            int x, y;
            SDL_GetMouseState(&x, &y);
            bodies[0]->position.x = x;
            bodies[0]->position.y = y;
            break;
        }
    }
}

void Application::Update() {
    Graphics::ClearScreen(0xFF0F0721);

    static int timePreviousFrame = 0;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0) {
        SDL_Delay(timeToWait);
    }

    float dt = (SDL_GetTicks() - timePreviousFrame) / 1000.f;
    if (dt > 0.016f) {
        dt = 0.016f;
    }
    timePreviousFrame = SDL_GetTicks();

    // Apply forces to bodies
    for (auto body : bodies) {
        // Vec2 weight = Vec2{0.f, 9.81 * PIXELS_PER_METER};
        // body->AddForce(weight);
        //
        // Vec2 wind = Vec2{10.f * PIXELS_PER_METER, 0.f};
        // body->AddForce(wind);
    }

    for (auto body : bodies) {
        body->Update(dt);
    }

    // Check Collision detection
    for (int i = 0; i < static_cast<int>(bodies.size()) - 1; ++i) {
        for (int j = i + 1; j < static_cast<int>(bodies.size()); ++j) {
            Body* a = bodies[i];
            Body* b = bodies[j];
            a->isColliding = false;
            b->isColliding = false;
            Contact contact;
            if (CollisionDetection::IsColliding(a, b, contact)) {
                Graphics::DrawFillCircle(contact.start.x, contact.start.y, 3.f,
                                         0XFFFFFFFF);
                Graphics::DrawFillCircle(contact.end.x, contact.end.y, 3.f,
                                         0XFFFFFFFF);
                Graphics::DrawLine(
                    contact.start.x, contact.start.y,
                    contact.start.x + contact.normal.x * contact.depth,
                    contact.start.y + contact.normal.y * contact.depth,
                    0XFFFFFFFF);

                a->isColliding = true;
                b->isColliding = true;
            }
        }
    }

    // Bounds correction
    for (auto body : bodies) {
        switch (body->shape->GetType()) {
        case ShapeType::Box: {
            break;
        }
        case ShapeType::Circle: {
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
            break;
        }
        case ShapeType::Polygon: {
            break;
        }
        }
    }
}

void Application::Render() {
    if (leftMouseButtonDown) {
        Graphics::DrawLine(bodies[0]->position.x, bodies[0]->position.y,
                           mouseCursor.x, mouseCursor.y, 0xFF313131);
    }

    for (auto body : bodies) {
        Uint32 color = body->isColliding ? 0XFF0000FF : 0XFFFFFFFF;

        switch (body->shape->GetType()) {
        case ShapeType::Box: {
            BoxShape* boxShape = static_cast<BoxShape*>(body->shape);
            Graphics::DrawPolygon(body->position.x, body->position.y,
                                  boxShape->worldVertices, color);
            break;
        }
        case ShapeType::Circle: {
            CircleShape* circleShape = static_cast<CircleShape*>(body->shape);
            Graphics::DrawCircle(body->position.x, body->position.y,
                                 circleShape->radius, body->rotation, color);
            break;
        }
        case ShapeType::Polygon: {
            break;
        };
        }
    }

    Graphics::RenderFrame();
}

void Application::Destroy() {
    for (auto body : bodies) {
        delete body;
    }
    bodies.clear();
    Graphics::CloseWindow();
}
