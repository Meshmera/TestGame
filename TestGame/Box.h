#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Enemy.h"

class Box {
public:
    Box(int offsetX, int offsetY, int size, SDL_Renderer* renderer);
    ~Box();

    void update(int playerX, int playerY);
    void render(SDL_Renderer* renderer);
    bool checkCollision(Enemy* enemy);

    int getX() const { return x; }
    int getY() const { return y; }
    int getSize() const { return size; }

private:
    int x, y;
    int size;
    int offsetX, offsetY;  
    SDL_Texture* texture;
};

