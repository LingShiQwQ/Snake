#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "config.h"

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

extern SDL_Window *win;
extern TTF_Font *fnt;
extern float window_x;
extern float window_y;
extern bool IsGameOver;

extern void EventLoop();

#endif



