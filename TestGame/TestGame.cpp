#include <iostream>
#include <vector>
#include <string>

#include <cstdlib>   // Для rand()
#include <ctime>     // Для srand()

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Player.h"
#include "Enemy.h"
#include "Box.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int spawnTimer = 0;
int spawnInterval = 100;  // Интервал появления врагов (кадры)

void renderText(SDL_Renderer* renderer, TTF_Font* font, int score) {
    SDL_Surface* surface = TTF_RenderText_Solid(font,
        ("Score: " + std::to_string(score)).c_str(),
        { 255, 255, 255 });
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect = { 10, 10, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void spawnEnemy(std::vector<Enemy*>& enemies, int screenWidth, int screenHeight, int score, SDL_Renderer* renderer) {
    int type = rand() % 3;  // Выбираем случайный тип врага (0, 1 или 2)
    int x = rand() % screenWidth;  // Случайная X координата
    int y = 0;  // Враги появляются сверху экрана
    int size = 10;
    double speed = 0.1 + (score / 100.0)*0.1;  // Увеличение скорости врагов по мере роста очков

    if (type == 0) {
        enemies.push_back(new StraightEnemy(x, y, size, speed, renderer));
    }
    else if (type == 1) {
        enemies.push_back(new ZigzagEnemy(x, y, size, speed, renderer));
    }
    else {
        enemies.push_back(new SpiralEnemy(x, y, size, speed, renderer));
    }
}

void renderGameOver(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Game Over! Press R to restart", { 255, 0, 0 });
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect textRect = { 200, 250, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Texture* backgroundTexture = nullptr;

    SDL_Window* window = SDL_CreateWindow("Mini-Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* bgSurface = IMG_Load("image_resource\\background.png");  // Файл должен быть в папке с игрой
    backgroundTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    TTF_Init();
    TTF_Font* font = TTF_OpenFont("font_resource\\arialmt.ttf", 24);
    SDL_Color white = { 255, 255, 255, 255 };

    Player player(400, 550, 50, renderer);
    Box box(-10, -10, 70, renderer);  // Смещение от игрока
    std::vector<Enemy*> enemies;
    int score = 0;
    double bgOffset = 0;
    double bgSpeed = 0.1;
    bool isGameOver = false;

    bool running = true;
    SDL_Event event;

    enemies.push_back(new StraightEnemy(100, 100, 10, 0.1, renderer));
    enemies.push_back(new ZigzagEnemy(100, 100, 10, 0.1, renderer));
    enemies.push_back(new SpiralEnemy(400, 300, 10, 0.1, renderer));

    srand(time(0));  // Инициализируем генератор случайных чисел

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            player.handleEvent(event);

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r && isGameOver) {
                    isGameOver = false;
                    score = 0;
                    enemies.clear();  // Удаляем всех врагов
                    spawnInterval = 100;
                }
            }
        }         

        player.update();  
        box.update(player.getX(), player.getY());

        SDL_Rect bgRect1 = { 0, bgOffset, 800, 600 };
        SDL_Rect bgRect2 = { 0, bgOffset - 600, 800, 600 };  // Второй кусок

        SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect1);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &bgRect2);

        renderText(renderer, font, score);

        player.render(renderer);
        box.render(renderer);            

        for (auto it = enemies.begin(); it != enemies.end();) {
            (*it)->update();
            (*it)->render(renderer);

            if (box.checkCollision(*it)) {  // Если враг попал в коробку — удаляем
                delete* it;
                it = enemies.erase(it);
                score += 10;
            }
            else if ((*it)->isOffScreen(SCREEN_HEIGHT)) {
                delete* it;
                it = enemies.erase(it);
            } else if ((*it)->getX() < player.getX() + player.getSize() &&
                (*it)->getX() + (*it)->getSize() > player.getX() &&
                (*it)->getY() < player.getY() + player.getSize() &&
                (*it)->getY() + (*it)->getSize() > player.getY()) {
                isGameOver = true;  // Если враг коснулся игрока — игра окончена
                break;
                }
                else {
                    ++it;
                }            
        }

        if (isGameOver) {
            renderGameOver(renderer, font);
            SDL_RenderPresent(renderer);
            continue;  // Останавливаем обновление объектов
        }

        bgOffset += bgSpeed;
        if (bgOffset >= 600) {  // Высота изображения (замени на свою)
            bgOffset = 0;
        }

        if (spawnTimer <= 0) {
            spawnEnemy(enemies, 800, 600, score, renderer);
            spawnTimer = spawnInterval;

            if (spawnInterval > 100) {  // Постепенное уменьшение времени спавна
                spawnInterval -= 1;
            }
        }
        spawnTimer--;    

        SDL_RenderPresent(renderer);
    } 

    SDL_DestroyTexture(backgroundTexture);

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

