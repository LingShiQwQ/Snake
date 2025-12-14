#ifndef DRAW_H
#define DRAW_H

#include "main.h"

extern bool InitRenders();
extern void DestroyRenderers();
extern void DrawAll();
extern void PresentRenders();
extern void DrawBackground();
extern void DrawBody();
extern void DrawFood();
extern void DrawScore();
extern void DrawGameOver();

#endif

