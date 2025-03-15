#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <cmath>

class Enemy {
public:
    Enemy(int startX, int startY, int size, int speed, SDL_Renderer* renderer);
    virtual ~Enemy();

    virtual void update(int playerX, int playerY) = 0;  // ƒвижение
    void render(SDL_Renderer* renderer);

    int getX() const { return x; }
    int getY() const { return y; }
    int getSize() const { return size; }

    bool isOffScreen(int screenHeight) const {
        return y > screenHeight || y < 0 || x < 0 || x > 800;
    }

protected:
    int x, y;
    int size;
    int speed;

    SDL_Texture* texture;
};

class StraightEnemy : public Enemy {
public:
    StraightEnemy(int startX, int startY, int size, int speed, SDL_Renderer* renderer);
    void update(int playerX, int playerY) override;
};

class ZigzagEnemy : public Enemy {
public:
    ZigzagEnemy(int startX, int startY, int size, int speed, SDL_Renderer* renderer);
    void update(int playerX, int playerY) override;

private:
    int direction = 1;  // 1 Ч вниз, -1 Ч вверх
};

class SpiralEnemy : public Enemy {
public:
    SpiralEnemy(int startX, int startY, int size, int speed, SDL_Renderer* renderer);
    void update(int playerX, int playerY) override;

private:
    float angle = 0;
};
