#pragma once

#include "resource.h"
#include <cmath>
#include <numbers>
#include <vector>
#include <memory>

#include "CObject.h"

void DrawCircle(const HDC& hdc, const POINT& center, const int& Radius)
{
	Ellipse(hdc, center.x - Radius, center.y - Radius, center.x + Radius, center.y + Radius);
}

void DrawSunflower(const HDC& hdc, const POINT& center, const int& Radius, const int& count = 3)
{
	double theta = std::numbers::pi * 2 / count;
	double halfTheta = theta / 2;
	double r2 = std::sin(halfTheta) * Radius / (1 - std::sin(halfTheta));

	DrawCircle(hdc, center, Radius);

	for (int i = 0; i < count; ++i)
	{
		POINT center2{ (Radius + r2) * std::cos(theta * i) + center.x, (Radius + r2) * std::sin(theta * i) + center.y };

		DrawCircle(hdc, center2, r2);
	}
}

void DrawStar(const HDC& hdc, const POINT& center, const int& radius)
{
	double theta{ std::numbers::pi * 2 / 5 };
	double tempLen{ radius * cos(theta) };
	double miniRadius{ tempLen / cos(theta / 2) };

	POINT points[5] = {};
	for (int i = 0; i < 5; ++i)
	{
		points[i].x = center.x + radius * cos(theta * i - theta / 4);
		points[i].y = center.y + radius * sin(theta * i - theta / 4);
	}

	POINT miniPoints[5] = {};
	for (int i = 0; i < 5; ++i)
	{
		miniPoints[i].x = center.x + miniRadius * cos(theta * i + theta / 2 - theta / 4);
		miniPoints[i].y = center.y + miniRadius * sin(theta * i + theta / 2 - theta / 4);
	}

	POINT realPoints[10] = {};
	for (int i = 0; i < 5; ++i)
	{
		realPoints[2 * i] = points[i];
		realPoints[2 * i + 1] = miniPoints[i];
	}

	Polygon(hdc, realPoints, 10);
}

void DrawCross(const HDC& hdc, const POINT& center, int length, int pos)
{
	int left{ center.x - length / 2 };
	int right{ center.x + length / 2 };
	int up{ center.y - length / 2 };
	int down{ center.y + length / 2 };

	HBRUSH brush = NULL, oldBrush = NULL;
	LPCWSTR s[4] = { L"위쪽", L"왼쪽", L"오른쪽", L"아래쪽" };
	int dir[4][2] = { {0, -1}, {-1, 0}, {1, 0}, {0, 1} };

	for (int i = 0; i < 4; ++i)
	{
		RECT rect = {
				left + length * dir[i][0],
				up + length * dir[i][1],
				right + length * dir[i][0],
				down + length * dir[i][1]
		};

		if (i == (pos - 1))
		{
			brush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, brush);

			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

			SelectObject(hdc, oldBrush);
			DeleteObject(brush);
		}
		else
		{
			Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			DrawText(hdc, s[i], wcslen(s[i]), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

void DrawObjects(const std::vector<std::unique_ptr<CObject>>& objects, const HDC& hdc)
{
	for (const auto& object : objects)
	{
		object->Draw(hdc);
	}
}