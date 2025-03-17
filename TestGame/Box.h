#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Enemy.h"

class Box {
public:
    Box(int offsetX, int offsetY, int width, int height, SDL_Renderer* renderer);
    ~Box();

    void update(int playerX, int playerY);
    void render(SDL_Renderer* renderer);
    bool checkCollision(Enemy* enemy);

    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
    int width, height;
    int offsetX, offsetY;  
    SDL_Texture* texture;
};

