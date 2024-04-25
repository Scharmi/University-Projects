#include "animator.h"
#include "models.h"
#include "game_state.h"
#include <windows.h>
#include <iostream>
#include <d2d1_3.h>
#include <wincodec.h>
#include <dwrite_3.h>
#include <cmath>
#include <wchar.h>
#include <string>
#include <sstream>
#include <wchar.h>
#include <numbers>
#include<vector>

using D2D1::ColorF;
using D2D1::Point2F;
using D2D1::BezierSegment;
using D2D1::QuadraticBezierSegment;
using D2D1::Matrix3x2F;
using D2D1::RectF;
using std::sin;
namespace {
    static ID2D1SolidColorBrush* brush1 = nullptr;
    static ID2D1SolidColorBrush* brush2 = nullptr;
    static ID2D1HwndRenderTarget* pRenderTarget = nullptr;
    static ID2D1SolidColorBrush* pBrush = nullptr;
    ID2D1PathGeometry* path = nullptr;
    ID2D1GeometrySink* path_sink = nullptr;
    ID2D1Factory* pD2DFactory = nullptr;
    IDWriteFactory* write_factory = nullptr;
    IDWriteTextFormat* text_format = nullptr;
    static float oldTime = 0.0f;
    static float speed = 0.0f;
    static float position = 0.0f;
    FLOAT const brush2_width = 3.0f;
    const float STARS = 100;
    static std::vector<Coords> star_coords;
    ID2D1Bitmap* asteroidBitmap = NULL;
    ID2D1Bitmap* rocketBitmap = NULL;
}
void InitializeDirect2D(HWND hwnd)
{
    for (int i = 0; i < STARS; i++) {
		star_coords.push_back(Coords(static_cast<FLOAT>(rand() % 1000), static_cast<FLOAT>(rand() % 1000)));
	}
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(IDWriteFactory),
        reinterpret_cast<IUnknown**>(&write_factory)
    );
    write_factory->CreateTextFormat(
        L"Comic Sans MS",
        nullptr,
        DWRITE_FONT_WEIGHT_BOLD,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        30.0f,
        L"en-us",
        &text_format
    );

    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
    RECT rc;
    GetClientRect(hwnd, &rc);

    pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            hwnd,
            D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)
        ),
        &pRenderTarget
    );
    pD2DFactory->CreatePathGeometry(&path);
    path->Open(&path_sink);
    path_sink->BeginFigure(Point2F(200, 300), D2D1_FIGURE_BEGIN_FILLED);
    path_sink->AddBezier(BezierSegment(
        Point2F(100, 150), Point2F(500, 150), Point2F(400, 300)
    ));
    path_sink->AddQuadraticBezier(QuadraticBezierSegment(
        Point2F(300, 450), Point2F(200, 300)
    ));
    path_sink->EndFigure(D2D1_FIGURE_END_OPEN);
    path_sink->Close();
    D2D1_COLOR_F const clear_color = {
    .r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f
    };
    D2D1_COLOR_F const brush1_color = {
        .r = 1.0f, .g = 0.5f, .b = 0.5f, .a = 1.0f
    };
    D2D1_COLOR_F const brush2_color = {
        .r = 1.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f
    };

    pRenderTarget->CreateSolidColorBrush(brush1_color, &brush1);
    pRenderTarget->CreateSolidColorBrush(brush2_color, &brush2);

    pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Blue),
        &pBrush
    );
    HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
		exit(1);
	}
    LoadBitmapFromFile(pRenderTarget, L"asteroid.png", &asteroidBitmap);
    LoadBitmapFromFile(pRenderTarget, L"rakieta.png", &rocketBitmap);
}

void Render(HWND hwnd, Rocket rocket, std::vector<Bullet> bullets, std::vector<Asteroid> asteroids, int score, int lives)
{

    PAINTSTRUCT ps;
    BeginPaint(hwnd, &ps);
    pRenderTarget->BeginDraw();
    pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
    RECT rc;
    GetClientRect(hwnd, &rc);
    animate_background(rc, pRenderTarget, pD2DFactory);
    animate_stars(rc, pRenderTarget, pD2DFactory, star_coords);
    animate_rocket(rc, pRenderTarget, pD2DFactory ,rocket, rocketBitmap);
    for (auto bullet : bullets) {
		animate_bullet(rc, pRenderTarget, pD2DFactory, bullet);
	}
    for (auto asteroid : asteroids) {
        animate_asteroid(rc, pRenderTarget, asteroid, asteroidBitmap);
    }
    animate_scoreboard(rc, pRenderTarget, text_format, score);
    animate_healthbar(rc, pRenderTarget, pD2DFactory, lives);
    HRESULT hr = pRenderTarget->EndDraw();
    if (FAILED(hr))
    {
        exit(1);
    }
    EndPaint(hwnd, &ps);
}

void CleanUpDirect2D()
{
    if (pBrush)
    {
        pBrush->Release();
        pBrush = nullptr;
    }
    if (pRenderTarget)
    {
        pRenderTarget->Release();
        pRenderTarget = nullptr;
    }
    if (pD2DFactory)
    {
        pD2DFactory->Release();
        pD2DFactory = nullptr;
    }
    if (text_format) text_format->Release();
    if (write_factory) write_factory->Release();

}
void Resize(LPARAM lParam) 
{
    if (FAILED(pRenderTarget->Resize(D2D1::SizeU(LOWORD(lParam), HIWORD(lParam)))))
    {
        exit(1);
    }
}
void LoadBitmapFromFile(
    ID2D1RenderTarget* m_pRenderTarget,
    PCWSTR uri,
    ID2D1Bitmap** ppBitmap
) {
    IWICImagingFactory* pIWICFactory = NULL;
    HRESULT hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pIWICFactory)
    );
    if (FAILED(hr)) exit(1);
    IWICBitmapDecoder* pDecoder = NULL;
    pIWICFactory->CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );
    IWICBitmapFrameDecode* pSource = NULL;
    pDecoder->GetFrame(0, &pSource);
    IWICFormatConverter* pConverter = NULL;
    pIWICFactory->CreateFormatConverter(&pConverter);
    pConverter->Initialize(
        pSource,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        NULL,
        0.0f,
        WICBitmapPaletteTypeMedianCut
    );
    m_pRenderTarget->CreateBitmapFromWicBitmap(
        pConverter,
        NULL,
        ppBitmap
    );
    pIWICFactory->Release();
    pDecoder->Release();
    pSource->Release();
    pConverter->Release();
}