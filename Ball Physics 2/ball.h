#pragma once
#include "vector.h"
#include <SDL.h>
#include <vector>
#include <cmath>

class Ball {
public:
    float x, y, r, ax0, ay0;
    Vector2D velocity;
    Vector2D acceleration;

    Ball(float x, float y, float r, float ax0, float ay0) 
        : x(x), y(y), r(r), velocity(0, 0), acceleration(ax0, 98 + ay0) {}

    void update(float dt) {
        velocity = velocity + acceleration * dt;
        x += velocity.x * dt;
        y += velocity.y * dt;

        int screenWidth, screenHeight;
        SDL_GetWindowSize(SDL_GetWindowFromID(1), &screenWidth, &screenHeight);

        if (x - r < 0) {
            x = r;
            velocity.x = -velocity.x * 0.8;
            acceleration.x = -acceleration.x * 0.8;
        } else if (x + r > screenWidth) {
            x = screenWidth - r;
            velocity.x = -velocity.x * 0.8;
            acceleration.x = -acceleration.x * 0.8;
        }

        if (y - r < 0) {
            y = r;
            velocity.y = -velocity.y;
            acceleration.y = 98;
        } else if (y + r > screenHeight) {
            y = screenHeight - r;
            velocity.y = -velocity.y * 0.8f;
            acceleration.y = 98;
        }
    }

    void draw(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int w = 0; w < r * 2; w++) {
            for (int h = 0; h < r * 2; h++) {
                int dx = r - w;
                int dy = r - h;
                if ((dx*dx + dy*dy) <= (r * r)) {
                    SDL_RenderDrawPoint(renderer, x + dx, y + dy);
                }
            }
        }
    }

    void resolveCollision(Ball& other) {
        Vector2D normal = (Vector2D(other.x, other.y) - Vector2D(x, y)).normalize();
        Vector2D relativeVelocity = other.velocity - velocity;
        float velocityAlongNormal = relativeVelocity.dot(normal);

        if (velocityAlongNormal > 0) return;

        float e = 0.8f;
        float m1 = M_PI * r * r;
        float m2 = M_PI * other.r * other.r;
        float impulseMagnitude = (-(1 + e) * velocityAlongNormal) / (1 / m1 + 1 / m2);
        Vector2D impulse = normal * impulseMagnitude;

        velocity = velocity - impulse * (1 / m1);
        other.velocity = other.velocity + impulse * (1 / m2);

        float overlap = (r + other.r) - (Vector2D(other.x, other.y) - Vector2D(x, y)).length();
        acceleration.x = 0;
        other.acceleration.x = 0;
        if (overlap > 0) {
            float totalMass = m1 + m2;
            float ratio1 = m2 / totalMass;
            float ratio2 = m1 / totalMass;

            x -= normal.x * overlap * ratio1;
            y -= normal.y * overlap * ratio1;
            other.x += normal.x * overlap * ratio2;
            other.y += normal.y * overlap * ratio2;
        }
    }
};
