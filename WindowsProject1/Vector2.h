#pragma once

#include <cmath>

class Vector2
{
public:
	float x;
	float y;

	explicit constexpr Vector2() : Vector2{ 0.0f, 0.0f }
	{

	}

	explicit constexpr Vector2(const float& x, const float& y) : x{ x }, y{ y }
	{

	}

	explicit constexpr Vector2(const int& x, const int& y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) }
	{

	}

	constexpr Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
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