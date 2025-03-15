#include "Player.h"

Player::Player(int startX, int startY, int size, SDL_Renderer* renderer)
    : x(startX), y(startY), size(size), speed(5), velX(0), velY(0) {

    SDL_Surface* surface = IMG_Load("image_resource\\ship.png");  // Загружаем картинку
    if (!surface) {
        //printf("Ошибка загрузки изображения: %s\n", IMG_GetError());
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
        case SDLK_UP:    velY = -speed; break;
        case SDLK_DOWN:  velY = speed;  break;
        case SDLK_LEFT:  velX = -speed; break;
        case SDLK_RIGHT: velX = speed;  break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_DOWN:  velY = 0; break;
        case SDLK_LEFT:
        case SDLK_RIGHT: velX = 0; break;
        }
    }
}

void Player::update() {
    x += velX;
    y += velY;

    // Ограничение передвижения в границах экрана
    if (x < 0) x = 0;
    if (x > 800 - size) x = 800 - size;
    if (y < 0) y = 0;
    if (y > 600 - size) y = 600 - size;
}

void Player::render(SDL_Renderer* renderer) {
    /*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect playerRect = { x, y, size, size };
    SDL_RenderFillRect(renderer, &playerRect);*/

    SDL_Rect rect = { x, y, size, size };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}