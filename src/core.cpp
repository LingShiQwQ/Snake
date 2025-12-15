#include "core.h"
#include "draw.h"

Food food;
Snake snake;

Food::Food()
{
    NewFood(0);
}
void Food::NewFood()
{
    x = rand() % ((int)window_x - FOOD_SIZE);
    y = rand() % ((int)window_y - FOOD_SIZE);
    rect = {x, y, FOOD_SIZE, FOOD_SIZE};

    //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[INFO]A NEW food was generated!");

    while (IsIntersection(&snake.head, &food.rect)) {
        //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[INFO]Called food.NewFood() in cycle while");
        food.NewFood();
    }
}
void Food::NewFood(const uint8_t INIT_MODE)
{
    srand(time(NULL));
    x = rand() % ((int)window_x - FOOD_SIZE);
    y = rand() % ((int)window_y - FOOD_SIZE);
    rect = {x, y, FOOD_SIZE, FOOD_SIZE};
}


Snake::Snake()
{
    best = 0;
    history_best = 0;
    InitValue();
}

void Snake::InitValue()
{
    x = window_x / 2;
    y = window_y / 2;
    len = START_LENGTH;
    dir = RIGHT;
    speed = SPEED;
    score = 0;
    head = {x - HEAD_SIZE / 2, y - HEAD_SIZE / 2, HEAD_SIZE, HEAD_SIZE};
    body.clear();
    body.push_back(head);
}

void Snake::Move()
{
    UpdateRect();
    oldx = x;
    oldy = y;

    uint8_t check = CheckBorder(body[0]);
    if (check != 0)
    {
        CorrectBorder(body[0], &x, &y, check);
        UpdateRect();
    }

    switch(dir)
    {
        case UP:
            y -= speed;
            break;
        case DOWN:
            y += speed;
            break;
        case LEFT:
            x -= speed;
            break;
        case RIGHT:
            x += speed;
            break;
        default:
            break;
    }

    for (int i = body.size() - 1; i > 0; i--)
    {
        body[i] = body[i - 1];
    }

    body[0] = {oldx - HEAD_SIZE / 2, oldy - HEAD_SIZE / 2, HEAD_SIZE, HEAD_SIZE};
    UpdateRect();
}
void Snake::ChangeDir(SDL_Event event)
{
    switch (event.key.key)
    {
        case SDLK_W:
        case SDLK_UP:
        if (dir != DOWN)
            dir = UP;
            break;
        case SDLK_S:
        case SDLK_DOWN:
        if (dir != UP)
            dir = DOWN;
            break;
        case SDLK_A:
        case SDLK_LEFT:
        if (dir != RIGHT)
            dir = LEFT;
            break;
        case SDLK_D:
        case SDLK_RIGHT:
        if (dir != LEFT)
            dir = RIGHT;
            break;
        default:
            break;
    }
}


uint8_t Snake::CheckBorder(SDL_FRect _rect)
{
    if (_rect.x + _rect.w <= 0)
    {
        return 1;
    }
    else if (_rect.x >= window_x)
    {
        return 2;
    }

    if (_rect.y + _rect.h <= 0)
    {
        return 3;
    }
    else if (_rect.y >= window_y)
    {
        return 4;
    }

    return 0;
}
void Snake::CorrectBorder(SDL_FRect _rect, float *_x, float *_y, uint8_t flag)
{
    switch(flag)
    {
        case 1:
            *_x = window_x;
            break;
        case 2:
            *_x = 0 - _rect.w / 2;
            break;
        case 3:
            *_y = window_y;
            break;
        case 4:
            *_y = 0 - _rect.h / 2;
            break;
        default:
            return;
    }
        
}

void Snake::UpdateRect()
{

    if (body.size() < len)
    {
        Grow();
    }
    else if (body.size() > len)
    {
        body.resize(len);
    }
/*
    if (!body.empty())
    {
        body[0] = head;

        for (size_t i = 1; i < body.size(); i++)
        {
            body[i] = body[i - 1];
        }
    }
*/
}

void Snake::Grow()
{
    SDL_FRect newSegment = body[body.size() - 4];
    body.push_back(newSegment);
}

void Snake::Eat()
{
    if (IsIntersection(&body[0], &food.rect))
    {
        //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[INFO]吃到食物！");
        len += 8;
        score++;
        food.NewFood();
        Grow();
    }
}
bool Snake::IsDead()
{

    smallHead = {
        body[0].x + body[0].w * 0.25f,
        body[0].y + body[0].h * 0.25f,
        body[0].w * 0.5f,
        body[0].h * 0.5f};

    for (size_t i = 10; i < body.size(); i++)
    {
        if (SDL_HasRectIntersectionFloat(&smallHead, &body[i]))
        {
            return true;
        }
    }
    return false;
}

bool IsIntersection(SDL_FRect *FRect_A, SDL_FRect *FRect_B)
{
    if (SDL_HasRectIntersectionFloat(FRect_A, FRect_B)) {
        return true;
    }
    return false;
}