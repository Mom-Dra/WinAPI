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

	explicit constexpr Vector2(float x, float y) : x{ x }, y{ y }
	{

	}

	explicit constexpr Vector2(int x, int y) : x{ static_cast<float>(x) }, y{ static_cast<float>(y) }
	{

	}

	constexpr Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	friend constexpr Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2{ a.x + b.x, a.y + b.y };
	}

	friend constexpr Vector2 operator*(const Vector2& v, float scalar)
	{
		return Vector2{ v.x * scalar, v.y * scalar };
	}

	Vector2 Normalize() const
	{
		float magnitude{ Magnitude() };
		return Vector2{ x / magnitude, y / magnitude };
	}

	float Magnitude() const
	{
		return std::sqrt(x * x + y * y);
	}
};