#include "CStar.h"
#include <numbers>

CStar::CStar(const Vector2& center, const int& speed, const int& radius, const int& count, const Vector2& moveDir) : CObject{ center, speed, moveDir }, radius{ radius }, count{ count }
{
	double theta{ std::numbers::pi * 2 / count };
	double tempLen{ radius * cos(theta) };
	double miniRadius{ tempLen / cos(theta / 2) };

	points.resize(count * 2);
	vPoints.resize(count * 2);

	for (int i = 0; i < count; ++i)
	{
		vPoints[2 * i].x = radius * cos(theta * i - theta / 4);
		vPoints[2 * i].y = radius * sin(theta * i - theta / 4);

		vPoints[2 * i + 1].x = miniRadius * cos(theta * i + theta / 2 - theta / 4);
		vPoints[2 * i + 1].y = miniRadius * sin(theta * i + theta / 2 - theta / 4);
	}

	transposeMatrix.SetTranslation(center);
	SetPoints(transposeMatrix);
}

void CStar::Update(const float& deltaTime)
{
	TranslateAndRotate(moveDir * speed * deltaTime, speed * deltaTime);
}

void CStar::Draw(const HDC& hdc) const
{
	Polygon(hdc, &points[0], count * 2);
}

bool CStar::Collision()
{
	return false;
}

void CStar::TranslateAndRotate(const Vector2& nV, float nAngle)
{
	SetCenter(center + nV);
	SetAngle(angle + nAngle);

	transposeMatrix.SetTranslationAndRotation(center, angle);

	SetPoints(transposeMatrix);
}

void CStar::SetPoints(const Matrix3x3& m)
{
	for (int i = 0; i < count * 2; ++i)
	{
		Vector2 nPoint = m * vPoints[i];
		points[i].x = static_cast<LONG>(nPoint.x);
		points[i].y = static_cast<LONG>(nPoint.y);
	}
}
