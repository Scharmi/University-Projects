#include "models.h"
#include "game_state.h"
#include <windows.h>
#include <iostream>
#include <d2d1_3.h>
#include <dwrite_3.h>
#include <wincodec.h>
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
    static ID2D1SolidColorBrush* pBrush = nullptr;
    ID2D1PathGeometry* path = nullptr;
    ID2D1GeometrySink* path_sink = nullptr;
    static float oldTime = 0.0f;
    static float speed = 0.0f;
    static float position = 0.0f;
    FLOAT const brush2_width = 3.0f;
    static float HEALTHBAR_Y_COORD = 100;
    static float HEART_WIDTH = 70;
}

void animate_rocket(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2DFactory, Rocket rocket, ID2D1Bitmap* pBitmap) {
    Coords coords = rocket.get_coords();
    pD2DFactory->CreatePathGeometry(&path);
    path->Open(&path_sink);
    float x_coord = rc.left + (rc.right - rc.left) * coords.x / 1000;
    float y_coord = rc.top + (rc.bottom - rc.top) * coords.y / 1000;
    pRenderTarget->DrawBitmap(
		pBitmap,
        D2D1::RectF(
			x_coord,
			y_coord,
			x_coord + 100,
			y_coord + 100
		)
	);
};
void animate_bullet(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2DFactory, Bullet bullet) {
    Coords coords = bullet.get_coords();
    pD2DFactory->CreatePathGeometry(&path);
    path->Open(&path_sink);
    float x_coord = rc.left + (rc.right - rc.left - 50) * coords.x / 1000;
    float y_coord = rc.top + (rc.bottom - rc.top - 50) * coords.y / 1000;
    path_sink->BeginFigure(
        D2D1::Point2F(x_coord, y_coord),
        D2D1_FIGURE_BEGIN_FILLED
    );
    path_sink->AddLine(D2D1::Point2F(x_coord + 2, y_coord));
    path_sink->AddLine(D2D1::Point2F(x_coord + 2, y_coord + 10));
    path_sink->AddLine(D2D1::Point2F(x_coord, y_coord + 10));
    path_sink->EndFigure(D2D1_FIGURE_END_CLOSED);
    path_sink->Close();
    pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Orange),
        &brush1
    );
    pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Orange),
        &brush2
    );
    pRenderTarget->FillGeometry(path, brush1);
    pRenderTarget->DrawGeometry(path, brush2, brush2_width);
}
void animate_asteroid(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, Asteroid asteroid, ID2D1Bitmap* pBitmap) {
    Coords coords = asteroid.get_coords();
    float radius = asteroid.get_radius();
    D2D1_MATRIX_3X2_F rotationMatrix = D2D1::Matrix3x2F::Rotation(
		asteroid.get_rotation(),
        D2D1::Point2F(
			rc.left + (rc.right - rc.left - 50) * coords.x / 1000,
			rc.top + (rc.bottom - rc.top - 50) * coords.y / 1000
		)
	);
    pRenderTarget->SetTransform(rotationMatrix);
    pRenderTarget->DrawBitmap(
        pBitmap,
        D2D1::RectF(
            rc.left + (rc.right - rc.left - 50) * coords.x / 1000 - radius,
            rc.top + (rc.bottom - rc.top - 50) * coords.y / 1000 - radius,
            rc.left + (rc.right - rc.left - 50) * coords.x / 1000 + radius,
            rc.top + (rc.bottom - rc.top - 50) * coords.y / 1000 + radius
        )
    );
    pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}
void animate_scoreboard(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, IDWriteTextFormat* text_format, int score) {
    std::wstringstream wss;
    wss << L"Score: " << score;
    HRESULT hr = pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White),
        &pBrush
    );
    if (FAILED(hr)) {
		std::cout << "Failed to create solid color brush" << std::endl;
	}
    std::wstring ws = wss.str();
    WCHAR NAPIS[40];
    wcscpy_s(NAPIS, ws.c_str());
    pRenderTarget->DrawText(
        NAPIS,
        (UINT32) ws.size(),
        text_format,
        RectF(
            static_cast<FLOAT>(rc.left) + (static_cast<FLOAT>(rc.right) - static_cast<FLOAT>(rc.left) - 50.0f) * 4.0f / 1000.0f, static_cast<FLOAT>(rc.top) + (static_cast<FLOAT>(rc.bottom) - static_cast<FLOAT>(rc.top) - 50.0f) * 4.0f / 1000.0f,
            static_cast<FLOAT>(rc.right),
            static_cast<FLOAT>(rc.bottom)
        ),
        pBrush
    );
}
void animate_healthbar(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2DFactory, int lives) {
    for (int i = 0; i < lives; i++) {
        animate_heart(rc, pRenderTarget, pD2DFactory, HEART_WIDTH/2 +  i * HEART_WIDTH, HEALTHBAR_Y_COORD);
    }
}
void animate_heart(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2DFactory, float x_coord, float y_coord) {
	pD2DFactory->CreatePathGeometry(&path);
	path->Open(&path_sink);
	x_coord = static_cast<FLOAT>(rc.left) + (static_cast<FLOAT>(rc.right) - static_cast<FLOAT>(rc.left)) * x_coord / 1000.0f;
	y_coord = static_cast<FLOAT>(rc.top) + (static_cast<FLOAT>(rc.bottom) - static_cast<FLOAT>(rc.top)) * y_coord / 1000.0f;
    path_sink->BeginFigure(
		D2D1::Point2F(x_coord, y_coord),
		D2D1_FIGURE_BEGIN_FILLED
	);
    path_sink->AddBezier(
        D2D1::BezierSegment(
			D2D1::Point2F(x_coord + 25, y_coord - 25),
			D2D1::Point2F(x_coord + 50, y_coord + 25),
			D2D1::Point2F(x_coord, y_coord + 50)
		)
	);
    path_sink->AddBezier(
        D2D1::BezierSegment(
			D2D1::Point2F(x_coord - 50, y_coord + 25),
			D2D1::Point2F(x_coord - 25, y_coord - 25),
			D2D1::Point2F(x_coord, y_coord)
		)
	);
	path_sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	path_sink->Close();
    D2D1::ColorF const color1 = D2D1::ColorF(D2D1::ColorF::Magenta, 1);
    ID2D1GradientStopCollection* pGradientStops = NULL;
    ID2D1LinearGradientBrush* m_pLinearGradientBrush;
    D2D1_GRADIENT_STOP gradientStops[2];
    gradientStops[0].color = color1;
    gradientStops[0].position = 0.0f;
    gradientStops[1].color = D2D1::ColorF(D2D1::ColorF::Red, 1);
    gradientStops[1].position = 1.0f;
    HRESULT hr = pRenderTarget->CreateGradientStopCollection(
        gradientStops,
        2,
        D2D1_GAMMA_2_2,
        D2D1_EXTEND_MODE_CLAMP,
        &pGradientStops
    );
    if (FAILED(hr)) {
        exit(1);
	}
    hr = pRenderTarget->CreateLinearGradientBrush(
        D2D1::LinearGradientBrushProperties(
            D2D1::Point2F(x_coord, y_coord),
            D2D1::Point2F(x_coord + 20, y_coord + 20)),
        pGradientStops,
        &m_pLinearGradientBrush
    );
    if (FAILED(hr)) {
		exit(1);
    }
    pRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::Black),
        &brush2
    );
    pRenderTarget->FillGeometry(path, m_pLinearGradientBrush);
    pRenderTarget->DrawGeometry(path, brush2, brush2_width);
}
void animate_background(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2DFactory) {
	pD2DFactory->CreatePathGeometry(&path);
	path->Open(&path_sink);
    path_sink->BeginFigure(
		D2D1::Point2F((float) rc.left, (float) rc.top),
		D2D1_FIGURE_BEGIN_FILLED
	);
	path_sink->AddLine(D2D1::Point2F((float) rc.right, (float) rc.top));
	path_sink->AddLine(D2D1::Point2F((float) rc.right, (float) rc.bottom));
	path_sink->AddLine(D2D1::Point2F((float) rc.left, (float) rc.bottom));
	path_sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	path_sink->Close();
    pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black),
		&brush1
	);
    pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Blue),
		&brush2
	);
	pRenderTarget->FillGeometry(path, brush1);
	pRenderTarget->DrawGeometry(path, brush2, brush2_width);
}
void animate_star(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, float x_coord, float y_coord) {
    D2D1_ELLIPSE ellipse = D2D1::Ellipse(
		D2D1::Point2F(rc.left + (rc.right - rc.left - 50) * x_coord / 1000,
            			rc.top + (rc.bottom - rc.top - 50) * y_coord / 1000),
		1,
		1
	);
    pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White), &brush1);

    pRenderTarget->FillEllipse(&ellipse, brush1);
}
void animate_stars(RECT rc, ID2D1HwndRenderTarget* pRenderTarget, ID2D1Factory* pD2DFactory, std::vector<Coords> star_coords) {
    for (int i = 0; i < 100; i++) {
		animate_star(rc, pRenderTarget, star_coords[i].x, star_coords[i].y);
	}
}
