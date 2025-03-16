#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <cmath>

class Enemy {
public:
    Enemy(int startX, int startY, int size, double speed, SDL_Renderer* renderer);
    virtual ~Enemy();

    virtual void update() = 0;  
    void render(SDL_Renderer* renderer);

    double getX() const { return x; }
    double getY() const { return y; }
    double getSize() const { return size; }

    bool isOffScreen(int screenHeight) const {
        return y > screenHeight || y < -50 || x < 0 || x > 800;
    }

protected:
    double x, y;
    int size;
    double speed;

    SDL_Texture* texture;
};

class StraightEnemy : public Enemy {
public:
    StraightEnemy(int startX, int startY, int size, double speed, SDL_Renderer* renderer);
    void update() override;
};

class ZigzagEnemy : public Enemy {
public:
    ZigzagEnemy(int startX, int startY, int size, double speed, SDL_Renderer* renderer);
    void update() override;

private:
    int direction = 1;  
    int turn = 1000;
};

class SpiralEnemy : public Enemy {
public:
    SpiralEnemy(int startX, int startY, int size, double speed, SDL_Renderer* renderer);
    void update() override;

private:
    double angle = 1.0;
};
