#pragma once
#ifndef MODELS_H
#define MODELS_H
#include "game_state.h"
#include <vector>
#include <windows.h>
#include <iostream>
#include <d2d1_3.h>
#include <dwrite_3.h>
#include <cmath>
#include <wchar.h>
#include <string>
#include <sstream>
#include <wchar.h>
#include <numbers>
#include<vector>

void animate_rocket(RECT, ID2D1HwndRenderTarget*, ID2D1Factory*, Rocket, ID2D1Bitmap*);
void animate_bullet(RECT, ID2D1HwndRenderTarget*, ID2D1Factory*, Bullet);
void animate_asteroid(RECT, ID2D1HwndRenderTarget*, Asteroid, ID2D1Bitmap*);
void animate_scoreboard(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* textFormat, int score);
void animate_healthbar(RECT, ID2D1HwndRenderTarget*, ID2D1Factory*, int);
void animate_heart(RECT, ID2D1HwndRenderTarget*, ID2D1Factory*, float, float);
void animate_background(RECT, ID2D1HwndRenderTarget*, ID2D1Factory*);
void animate_star(RECT, ID2D1HwndRenderTarget*, int, int);
void animate_stars(RECT, ID2D1HwndRenderTarget*, ID2D1Factory*, std::vector<Coords>);

#endif