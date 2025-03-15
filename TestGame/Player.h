#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Player {
public:
    Player(int startX, int startY, int size, SDL_Renderer* renderer);
    ~Player();

    void handleEvent(SDL_Event& event);
    void update();
    void render(SDL_Renderer* renderer);

    int getX() const { return x; }
    int getY() const { return y; }
    int getSize() const { return size; }

private:
    int x, y;  // Координаты игрока
    int size;  // Размер игрока
    int speed; // Скорость движения
    int velX, velY; // Скорость по осям

    SDL_Texture* texture;  // Текстура игрока
};

