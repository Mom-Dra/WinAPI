#pragma once
#include <array>
#include <stdexcept>
#include "Vector2.h"

class Vector3
{
public:
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 One;
	static const Vector3 Zero;
	static constexpr int Dimension{ 3 };

	union
	{
		struct
		{
			float x, y, z;
		};

		std::array<float, Dimension> Scalars;
	};

public:
	inline explicit constexpr Vector3();
	inline explicit constexpr Vector3(const Vector2& InV, bool IsPpint = true);
	inline explicit constexpr Vector3(float InX, float InY, float InZ);

	inline constexpr float operator[](int index) const;
	inline constexpr float& operator[](int index);
	inline constexpr Vector3 operator-() const;
	inline friend constexpr Vector3 operator*(const Vector3& v, float InScale);
	inline friend constexpr Vector3 operator/(const Vector3& v, float InScale);
	inline friend constexpr Vector3 operator*(const Vector3& a, const Vector3& b);
	inline friend constexpr Vector3 operator+(const Vector3& a, const Vector3& b);
	inline friend constexpr Vector3 operator-(const Vector3& a, const Vector3& b);

	inline constexpr Vector3& operator*=(float InScale);
	inline constexpr Vector3& operator/=(float InScale);
	inline constexpr Vector3& operator+=(const Vector3& InVector);
	inline constexpr Vector3& operator-=(const Vector3& InVector);

	inline constexpr float Dot(const Vector3& InVector) const;
	inline constexpr Vector2 ToVector2() const;
};

inline constexpr Vector3::Vector3() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f }
{

}

inline constexpr Vector3::Vector3(const Vector2& InV, bool IsPoint) : x{ InV.x }, y{ InV.y }, z{ IsPoint ? 1.0f : 0.0f }
{

}

inline constexpr Vector3::Vector3(float InX, float InY, float InZ) : x{ InX }, y{ InY }, z{ InZ }
{

}

inline constexpr float Vector3::operator[](int index) const
{
	if (index < 0 || index >= Dimension)
		throw std::out_of_range("Index out of range");

	return Scalars[index];
}

inline constexpr float& Vector3::operator[](int index)
{
	if (index < 0 || index >= Dimension)
		throw std::out_of_range("Index out of range");

	return Scalars[index];
}

inline constexpr Vector3 Vector3::operator-() const
{
	return Vector3{ -x, -y, -z };
}

inline constexpr Vector3& Vector3::operator*=(float InScale)
{
	x *= InScale;
	y *= InScale;
	z *= InScale;

	return *this;
}

inline constexpr Vector3& Vector3::operator/=(float InScale)
{
	x /= InScale;
	y /= InScale;
	z /= InScale;

	return *this;
}

inline constexpr Vector3& Vector3::operator+=(const Vector3& InVector)
{
	x += InVector.x;
	y += InVector.y;
	z += InVector.z;

	return *this;
}

inline constexpr Vector3& Vector3::operator-=(const Vector3& InVector)
{
	x -= InVector.x;
	y -= InVector.y;
	z -= InVector.z;

	return *this;
}

inline constexpr float Vector3::Dot(const Vector3& InVector) const
{
	return x * InVector.x + y * InVector.y + z * InVector.z;
}

inline constexpr Vector2 Vector3::ToVector2() const
{
	return Vector2{ x, y };
}

inline constexpr Vector3 operator*(const Vector3& v, float InScale)
{
	return Vector3{ v.x * InScale, v.y * InScale, v.z * InScale };
}

inline constexpr Vector3 operator/(const Vector3& v, float InScale)
{
	return Vector3{ v.x / InScale, v.y / InScale, v.z / InScale };
}

inline constexpr Vector3 operator*(const Vector3& a, const Vector3& b)
{
	return Vector3{ a.x * b.x, a.y * b.y, a.z * b.z };
}

inline constexpr Vector3 operator+(const Vector3& a, const Vector3& b)
{
	return Vector3{ a.x + b.x, a.y + b.y, a.z + b.z };
}

inline constexpr Vector3 operator-(const Vector3& a, const Vector3& b)
{
	return Vector3{ a.x - b.x, a.y - b.y, a.z - b.z };
}