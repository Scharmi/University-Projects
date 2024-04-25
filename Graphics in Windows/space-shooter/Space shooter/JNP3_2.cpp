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
#include <numbers>
#include "animator.h"
#include "game_state.h"
#include<vector>
using D2D1::ColorF;
using D2D1::Point2F;
using D2D1::BezierSegment;
using D2D1::QuadraticBezierSegment;
using D2D1::Matrix3x2F;
using D2D1::RectF;
using std::sin;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
GameState game_state;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Space shooter";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Space shooter",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );
    if (hwnd == nullptr)
    {
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


int oldTime = 0;
int newTime = 0;
int time_diff = 0;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        InitializeDirect2D(hwnd);
        SetTimer(hwnd, 1, 10, NULL);
        return 0;

    case WM_TIMER:
        InvalidateRect(hwnd, NULL, FALSE);
        return 0;

    case WM_PAINT:
        if (oldTime == 0) oldTime = GetTickCount();
        newTime = GetTickCount();
        PressedKeys keys;
        keys.up = GetAsyncKeyState(VK_UP);
        keys.down = GetAsyncKeyState(VK_DOWN);
        keys.left = GetAsyncKeyState(VK_LEFT);
        keys.right = GetAsyncKeyState(VK_RIGHT);
        keys.space = GetAsyncKeyState(VK_SPACE);
        time_diff = newTime - oldTime;
        oldTime = newTime;
        game_state.update(keys, time_diff);
        Render(hwnd, game_state.get_rocket(), game_state.get_bullets(), game_state.get_asteroids(), game_state.get_score(), game_state.get_lives());
        ValidateRect(hwnd, nullptr);
        return 0;

    case WM_DESTROY:
        KillTimer(hwnd, 1);
        CleanUpDirect2D();
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
		Resize(lParam); 
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}