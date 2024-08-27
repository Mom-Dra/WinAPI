#pragma once

#include <cmath>

struct Vector2
{
public:
	float x;
	float y;

	explicit Vector2(const float& x, const float& y) : x{ x }, y{ y }
	{

	}

	explicit Vector2(const int& x, const int& y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) }
	{

	}

	Vector2 Normalize() const
	{
		float magnitude{ Magnitude() };
		return Vector2{ x / magnitude, y / magnitude };
	}

	float Magnitude() const
	{
		return std::sqrtf(x * x + y * y);
	}
};