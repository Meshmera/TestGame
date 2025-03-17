#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int startX, int startY, int size, double speed, SDL_Renderer* renderer)
    : x(startX), y(startY), size(size), speed(speed) {

    SDL_Surface* surface = IMG_Load("image_resource\\meteor.png");  
    if (!surface) {
        std::cout << "Ошибка загрузки изображения: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
}

void Enemy::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { x, y, size, size };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool Enemy::isOffScreen(int screenHeight) const {
    return y > screenHeight || y < -50 || x < 0 || x > 800;
}

StraightEnemy::StraightEnemy(int startX, int startY, int size, double speed, SDL_Renderer* renderer)
    : Enemy(startX, startY, size, speed, renderer) {
}

void StraightEnemy::update() {
    y += speed;
}

ZigzagEnemy::ZigzagEnemy(int startX, int startY, int size, double speed, SDL_Renderer* renderer)
    : Enemy(startX, startY, size, speed, renderer) {
}

void ZigzagEnemy::update() {
    x += direction * speed;
    y += speed;

    if (y <= 0 || y >= 600 - size || turn == 0) {
        direction *= -1; 
        turn = 1000;
    }
    turn--;
}

SpiralEnemy::SpiralEnemy(int startX, int startY, int size, double speed, SDL_Renderer* renderer)
    : Enemy(startX, startY, size, speed, renderer) {
}

void SpiralEnemy::update() {
    angle += 5.0;
    x += cos(angle) * 30.0;
    y += sin(angle) * 30.0 + speed;
}