#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H
#ifndef UNICODE
#define UNICODE
#endif
#define CIRCLES 7
#define SQUEEZESPEED 5
#define SQUEEZESIZE 5
#define COLORSPEED 10

#include <windows.h>
#include <d2d1_3.h>
#include <dwrite_3.h>
#include <cmath>
#include <wchar.h>
#include <string>
#include <sstream>
#include <wchar.h>
#include "game_state.h"
#include <numbers>
#include<vector>
using D2D1::ColorF;
using D2D1::Point2F;
using D2D1::BezierSegment;
using D2D1::QuadraticBezierSegment;
using D2D1::Matrix3x2F;
using D2D1::RectF;
using std::sin;
void InitializeDirect2D(HWND hwnd);
void Render(HWND, Rocket, std::vector<Bullet>, std::vector<Asteroid>, int, int);
void CleanUpDirect2D();
void Resize(LPARAM);
void LoadBitmapFromFile(
    ID2D1RenderTarget* pRenderTarget,
    PCWSTR uri,
    ID2D1Bitmap** ppBitmap
);
#endif
