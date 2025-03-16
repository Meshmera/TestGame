#include "Box.h"
#include <iostream>

Box::Box(int offsetX, int offsetY, int size, SDL_Renderer* renderer)
    : offsetX(offsetX), offsetY(offsetY), size(size), x(0), y(0) {

    SDL_Surface* surface = IMG_Load("image_resource\\shield.png"); 
    if (!surface) {
        std::cout << "Ошибка загрузки изображения: " << IMG_GetError() << std::endl;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

Box::~Box() {
    SDL_DestroyTexture(texture);
}

void Box::update(int playerX, int playerY) {
    x = playerX + offsetX;
    y = playerY + offsetY;
}

void Box::render(SDL_Renderer* renderer) {
    SDL_Rect rect = { x, y, size, 10 };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

bool Box::checkCollision(Enemy* enemy) {
    int ex = enemy->getX();
    int ey = enemy->getY();
    int esize = enemy->getSize();

    return (x < ex + esize && x + size > ex &&
        y < ey + esize && y + 10/*size*/ > ey);
}
