#include "Player.h"
#include <iostream>

Player::Player(int startX, int startY, int size, SDL_Renderer* renderer)
    : x(startX), y(startY), size(size), speed(5), velX(0) {

    SDL_Surface* surface = IMG_Load("image_resource\\ship.png"); 
    if (!surface) {
        std::cout << "Ошибка загрузки изображения: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Player::~Player() {
    SDL_DestroyTexture(texture);
}

void Player::handleEvent(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:  velX = -1.0; break;
        case SDLK_RIGHT: velX = 1.0;  break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_RIGHT: velX = 0; break;
        }
    }
}

void Player::update() {
    x += velX;

    if (x < 0) x = 0;
    if (x > 800 - size) x = 800 - size;
    if (y < 0) y = 0;
    if (y > 600 - size) y = 600 - size;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { x, y, size, size };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}