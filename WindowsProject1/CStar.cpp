#include "CStar.h"
#include <numbers>

CStar::CStar(const Vector2& center, const int& speed, const int& radius, const int& count, const Vector2& moveDir) : CObject{ center, speed, moveDir }, radius{ radius }, count{ count }
{
	double theta{ std::numbers::pi * 2 / count };
	double tempLen{ radius * cos(theta) };
	double miniRadius{ tempLen / cos(theta / 2) };

	points.resize(count * 2);

	for (int i = 0; i < count; ++i)
	{
		points[2 * i].x = center.x + radius * cos(theta * i - theta / 4);
		points[2 * i].y = center.y + radius * sin(theta * i - theta / 4);

		points[2 * i + 1].x = center.x + miniRadius * cos(theta * i + theta / 2 - theta / 4);
		points[2 * i + 1].y = center.y + miniRadius * sin(theta * i + theta / 2 - theta / 4);
	}
}

void CStar::Update(const float& deltaTime)
{
	
}

void CStar::Draw(const HDC& hdc) const
{
	Polygon(hdc, &points[0], count * 2);
}

bool CStar::Collision()
{
	return false;
}
