#include <SDL.h>
#include <vector>
#include <iostream>
#include <cmath> 
#include <array>
#include "ball.h"
#include "read.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int ITERATIONS = 8;
const float DEFAULT_BALL_RADIUS = 20.0f;
std::vector<Ball> balls;

void updateAll(float dt) {
    for (auto& ball : balls) {
        ball.update(dt);
    }

    for (int i = 0; i < ITERATIONS; i++) {
        for (size_t j = 0; j < balls.size(); j++) {
            for (size_t k = j + 1; k < balls.size(); k++) { 
                auto& b1 = balls[j];
                auto& b2 = balls[k];
                float dist = std::sqrt((b2.x - b1.x) * (b2.x - b1.x) + (b2.y - b1.y) * (b2.y - b1.y));
                if (dist < b1.r + b2.r) {
                    b1.resolveCollision(b2);
                }
            }
        }
    }
}

void drawAll(SDL_Renderer* renderer) {
    for (const auto& ball : balls) {
        ball.draw(renderer);
    }
}

void runSimulation(const std::vector<std::vector<float>>& ballData) {
    for (const auto& data : ballData) {
        if (data.size() == 5) {
            balls.emplace_back(data[0], data[1], data[2], data[3], data[4]);
        } else {
            std::cerr << "Line does not have enough data: " << data.size() << " values." << std::endl;
        }
    }
}

const std::array<const char*, 9> simulationFiles = {
    "simulations/1.ball",
    "simulations/2.ball",
    "simulations/3.ball",
    "simulations/4.ball",
    "simulations/5.ball",
    "simulations/6.ball",
    "simulations/7.ball",
    "simulations/8.ball",
    "simulations/9.ball"
};

void handleEvents(SDL_Event& event, bool& running, bool& simulationRunning) {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT && !simulationRunning) {
                    balls.emplace_back(event.button.x, event.button.y, DEFAULT_BALL_RADIUS, 0, 0);
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_SPACE:
                        balls.clear();
                        std::cout << "Cleared all balls." << std::endl;
                        break;
                    case SDLK_1: case SDLK_2: case SDLK_3: 
                    case SDLK_4: case SDLK_5: case SDLK_6:
                    case SDLK_7: case SDLK_8: case SDLK_9: {
                        if (!simulationRunning) {
                            balls.clear();
                            int simulationIndex = event.key.keysym.sym - SDLK_1; 
                            if (simulationIndex >= 0 && simulationIndex < simulationFiles.size()) {
                                runSimulation(parse(simulationFiles[simulationIndex]));
                                simulationRunning = true;
                            }
                        }
                        break;
                    }
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym >= SDLK_1 && event.key.keysym.sym <= SDLK_9) {
                    balls.clear();
                    simulationRunning = false;
                }
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Ball Physics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    bool simulationRunning = false;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        handleEvents(event, running, simulationRunning);

        updateAll(dt * 3);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawAll(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
