#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int startX, int startY, int size, int speed, SDL_Renderer* renderer)
    : x(startX), y(startY), size(size), speed(speed) {

    SDL_Surface* surface = IMG_Load("image_resource\\meteor.png");  // Загружаем картинку
    if (!surface) {
        //printf("Ошибка загрузки изображения: %s\n", IMG_GetError());
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Enemy::~Enemy() {
    SDL_DestroyTexture(texture);
}

void Enemy::render(SDL_Renderer* renderer) {
    /*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { x, y, size, size };
    SDL_RenderFillRect(renderer, &rect);*/

    SDL_Rect rect = { x, y, size, size };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

StraightEnemy::StraightEnemy(int startX, int startY, int size, int speed, SDL_Renderer* renderer)
    : Enemy(startX, startY, size, speed, renderer) {
}

void StraightEnemy::update(int playerX, int playerY) {
    if (x < playerX) x += speed;
    if (x > playerX) x -= speed;
    if (y < playerY) y += speed;
    if (y > playerY) y -= speed;
}

ZigzagEnemy::ZigzagEnemy(int startX, int startY, int size, int speed, SDL_Renderer* renderer)
    : Enemy(startX, startY, size, speed, renderer) {
}

void ZigzagEnemy::update(int playerX, int playerY) {
    x += speed;
    y += direction * speed;

    if (y <= 0 || y >= 600 - size) {
        direction *= -1;  // Меняем направление
    }
}

SpiralEnemy::SpiralEnemy(int startX, int startY, int size, int speed, SDL_Renderer* renderer)
    : Enemy(startX, startY, size, speed, renderer) {
}

void SpiralEnemy::update(int playerX, int playerY) {
    angle += 0.1f;
    x += cos(angle) * speed;
    y += sin(angle) * speed;

    x += 1 * speed;
    y += 1 * speed;
}