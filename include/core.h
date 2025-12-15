#ifndef CORE_H
#define CORE_H

#include "main.h"

enum DIR
{
    UP = 1,
    DOWN,
    LEFT = 10,
    RIGHT
};

class Food
{
public:
    float x;
    float y;
    SDL_FRect rect;

    Food();
    void NewFood();
    void NewFood(const uint8_t INIT_MODE);
};
extern Food food;

class Snake
{
public:
    float x;
    float y;
    float oldx;
    float oldy;

    uint8_t dir;
    SDL_FRect head;
    float speed;

    int score;
    int history_best;
    int best;

    vector<SDL_FRect> body;
    uint32_t len;

    Snake();
    void InitValue();
    void Move();
    void Eat();
    void Grow();
    void ChangeDir(SDL_Event event);
    bool IsDead();
    void UpdateRect();

private:
    SDL_FRect smallHead;
    uint8_t CheckBorder(SDL_FRect _rect);
    void CorrectBorder(SDL_FRect _rect, float *_x, float *_y, uint8_t flag);
    
    
};
extern Snake snake;

bool IsIntersection(SDL_FRect *FRect_A, SDL_FRect *FRect_B);

#endif