#include "main.h"
#include "draw.h"
#include "core.h"

SDL_Window *win;
TTF_Font *fnt;

float window_x = WINDOW_W;
float window_y = WINDOW_H;
bool IsGameOver = false;
bool IsStartedNewGame = false;

void GameTick()
{
    snake.Move();
    snake.Eat();
    DrawAll();
    
    IsGameOver = snake.IsDead();
}
void RestartGame()
{
    IsGameOver = false;
    IsStartedNewGame = true;

    snake.InitValue();
    food.NewFood();
}

void GameOver()
{
    if (snake.history_best < snake.score) {
        std::ofstream file("./record.txt", std::ios::out);
        file << snake.score;
        
    }
    if (snake.best < snake.score) {
        snake.best = snake.score;
    }
    

    SDL_Event ev;
    DrawGameOver();
    SDL_Delay(1250);
    while (SDL_PollEvent(&ev));

    while (true) 
    {
        while (SDL_PollEvent(&ev))
        {
            if (ev.type == SDL_EVENT_QUIT)
                return;
            if (ev.type == SDL_EVENT_KEY_DOWN) {
                if (ev.key.key == SDLK_ESCAPE)
                    return;
                else {
                    RestartGame();
                    return;
                }
                  
            }
        }
    }
}
void EventLoop()
{
    SDL_Event event;
    bool isChangedValueOfSpeed = false;

    while (!IsGameOver)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                {
                    IsGameOver = true;
                    
                    if (snake.history_best < snake.score)
                    {
                        std::ofstream file("./record.txt", std::ios::out);
                        file << snake.score;
                        file.close();
                    }
                    return;
                }
                case SDL_EVENT_WINDOW_RESIZED:
                {
                    DrawAll();
                    break;
                }
                case SDL_EVENT_MOUSE_MOTION:
                {
                    //SDL_Log("x: %2f, y: %2f", event.motion.x, event.motion.y);
                    break;
                }
                case SDL_EVENT_KEY_DOWN:
                {
                    if (!isChangedValueOfSpeed && event.key.key == SDLK_LSHIFT || event.key.key == SDLK_RSHIFT) {
                        snake.speed = 2 * SPEED;
                        isChangedValueOfSpeed = true;
                    }
                    snake.ChangeDir(event);
                    break;
                }
                case SDL_EVENT_KEY_UP:
                {
                    if (event.key.key == SDLK_LSHIFT || event.key.key == SDLK_RSHIFT) {
                        snake.speed = SPEED;
                        isChangedValueOfSpeed = false;
                    }
                    break;
                }

                default:
                {
                    break;
                }
            }
        }
        SDL_Delay(20);
        
        GameTick();

    }

    GameOver();
}

bool InitGame()
{
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        SDL_Log("SDL_Init() failed: %s", SDL_GetError());
        return false;
    }
    //SDL_Log("SDL Init completed");

    if (!TTF_Init()) {
        SDL_Log("TTF_Init() failed: %s", SDL_GetError());
        return false;
    }
    //SDL_Log("SDL TTF Init completed");

    win = SDL_CreateWindow("Snake", window_x, window_y, 0);
    if (win == nullptr)
    {
        SDL_Log("SDL_CreateWindow() failed: %s", SDL_GetError());
        return false;
    }
    //SDL_Log("SDL Window created");

    if (!InitRenders())
    {
        cerr << "Func: InitRenders() failed \n";
        return false;
    }
    //SDL_Log("Renderers Init completed");

    fnt = TTF_OpenFont("D:/Codes/Project_Game/Snake/bin/res/fonts/Snake.ttf", 24);
    if (fnt == nullptr) {
        SDL_Log("TTF_OpenFont() failed: %s", SDL_GetError());
    }
    //SDL_Log("Fonts file opened");

    IsGameOver = false;

    std::ifstream file;
    file.open("./record.txt", std::ios::in);
    if (!file.is_open())
    {
        SDL_Log("Open record.txt failed");
        std::ofstream ofile;
        ofile.open("./record.txt", std::ios::out);
        ofile.close();
        file.open("./record.txt", std::ios::in);
    }

    file >> snake.history_best;

    SDL_Log("%d", snake.history_best);

    file.close();

    return true;
}
void QuitGame()
{
    DestroyRenderers();
    TTF_CloseFont(fnt);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char** argv)
{
    if (!InitGame()) {
        cerr << "Func: InitGame() failed\n";
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    do{
        EventLoop();
    } while (IsGameOver == false && IsStartedNewGame == true);

    QuitGame();
    return 0;
}