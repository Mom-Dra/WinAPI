#pragma once
#include <cmath>

class Vector2
{
public:
	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;

	float x;
	float y;

	inline explicit constexpr Vector2() noexcept;
	inline explicit constexpr Vector2(float x, float y) noexcept;
	inline explicit constexpr Vector2(int x, int y) noexcept;

	inline constexpr Vector2& operator+=(const Vector2& other) noexcept;
	inline constexpr Vector2 operator-() const noexcept;
	inline friend constexpr Vector2 operator+(const Vector2& a, const Vector2& b);
	inline friend constexpr Vector2 operator-(const Vector2& a, const Vector2& b);
	inline friend constexpr Vector2 operator*(const Vector2& v, float scalar);

	inline Vector2 Normalize() const;
	inline float Magnitude() const;
	inline constexpr float Dot(const Vector2& other) const;
};

inline constexpr Vector2::Vector2() noexcept : Vector2{ 0.0f, 0.0f }
{

}

inline constexpr Vector2::Vector2(float x, float y) noexcept : x{ x }, y{ y }
{

}

inline constexpr Vector2::Vector2(int x, int y) noexcept : Vector2{ static_cast<float>(x), static_cast<float>(y) }
{

}

inline constexpr Vector2& Vector2::operator+=(const Vector2& other) noexcept
{
	x += other.x;
	y += other.y;

	return *this;
}

inline constexpr Vector2 Vector2::operator-() const noexcept
{
	return Vector2{ -x, -y };
}

inline constexpr Vector2 operator+(const Vector2& a, const Vector2& b)
{
	return Vector2{ a.x + b.x, a.y + b.y };
}

inline constexpr Vector2 operator-(const Vector2& a, const Vector2& b)
{
	return Vector2{ a.x - b.x, a.y - b.y };
}

inline constexpr Vector2 operator*(const Vector2& v, float scalar)
{
	return Vector2{ v.x * scalar, v.y * scalar };
}

inline Vector2 Vector2::Normalize() const
{
	float magnitude{ Magnitude() };
	return Vector2{ x / magnitude, y / magnitude };
}

inline float Vector2::Magnitude() const
{
	return std::sqrt(x * x + y * y);
}

inline constexpr float Vector2::Dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}