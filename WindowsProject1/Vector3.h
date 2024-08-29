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
	explicit constexpr Vector3();
	explicit constexpr Vector3(const Vector2& InV, bool IsPpint = true);
	explicit constexpr Vector3(float InX, float InY, float InZ);

	constexpr float operator[](int index) const;
	constexpr float& operator[](int index);
	constexpr Vector3 operator-() const;
	friend constexpr Vector3 operator*(const Vector3& v, float InScale);
	friend constexpr Vector3 operator/(const Vector3& v, float InScale);
	friend constexpr Vector3 operator*(const Vector3& a, const Vector3& b);
	friend constexpr Vector3 operator+(const Vector3& a, const Vector3& b);
	friend constexpr Vector3 operator-(const Vector3& a, const Vector3& b);

	constexpr Vector3& operator*=(float InScale);
	constexpr Vector3& operator/=(float InScale);
	constexpr Vector3& operator+=(const Vector3& InVector);
	constexpr Vector3& operator-=(const Vector3& InVector);

	constexpr float Dot(const Vector3& InVector) const;
	constexpr Vector2 ToVector2() const;
};

constexpr Vector3::Vector3() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f }
{

}

constexpr Vector3::Vector3(const Vector2& InV, bool IsPoint) : x{ InV.x }, y{ InV.y }, z{ IsPoint ? 1.0f : 0.0f }
{

}

constexpr Vector3::Vector3(float InX, float InY, float InZ) : x{ InX }, y{ InY }, z{ InZ }
{

}

constexpr float Vector3::operator[](int index) const
{
	if (index < 0 || index >= Dimension)
		throw std::out_of_range("Index out of range");

	return Scalars[index];
}

constexpr float& Vector3::operator[](int index)
{
	if (index < 0 || index >= Dimension)
		throw std::out_of_range("Index out of range");

	return Scalars[index];
}

constexpr Vector3 Vector3::operator-() const
{
	return Vector3{ -x, -y, -z };
}

constexpr Vector3& Vector3::operator*=(float InScale)
{
	x *= InScale;
	y *= InScale;
	z *= InScale;

	return *this;
}

constexpr Vector3& Vector3::operator/=(float InScale)
{
	x /= InScale;
	y /= InScale;
	z /= InScale;

	return *this;
}

constexpr Vector3& Vector3::operator+=(const Vector3& InVector)
{
	x += InVector.x;
	y += InVector.y;
	z += InVector.z;

	return *this;
}

constexpr Vector3& Vector3::operator-=(const Vector3& InVector)
{
	x -= InVector.x;
	y -= InVector.y;
	z -= InVector.z;

	return *this;
}

constexpr float Vector3::Dot(const Vector3& InVector) const
{
	return x * InVector.x + y * InVector.y + z * InVector.z;
}

constexpr Vector2 Vector3::ToVector2() const
{
	return Vector2{ x, y };
}

constexpr Vector3 operator*(const Vector3& v, float InScale)
{
	return Vector3{ v.x * InScale, v.y * InScale, v.z * InScale };
}

constexpr Vector3 operator/(const Vector3& v, float InScale)
{
	return Vector3{ v.x / InScale, v.y / InScale, v.z / InScale };
}

constexpr Vector3 operator*(const Vector3& a, const Vector3& b)
{
	return Vector3{ a.x * b.x, a.y * b.y, a.z * b.z };
}

constexpr Vector3 operator+(const Vector3& a, const Vector3& b)
{
	return Vector3{ a.x + b.x, a.y + b.y, a.z + b.z };
}

constexpr Vector3 operator-(const Vector3& a, const Vector3& b)
{
	return Vector3{ a.x - b.x, a.y - b.y, a.z - b.z };
}