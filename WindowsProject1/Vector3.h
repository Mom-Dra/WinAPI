#pragma once
#include <array>
#include "Vector2.h"
//#include "Matrix3x3.h"

class Vector3
{
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

	constexpr Vector3& operator*=(const class Matrix3x3& m);
	constexpr Vector3& operator*=(float InScale);
	constexpr Vector3& operator/=(float InScale);
	constexpr Vector3& operator+=(const Vector3& InVector);
	constexpr Vector3& operator-=(const Vector3& InVector);

	constexpr float Dot(const Vector3& InVector) const;
	constexpr Vector2 ToVector2() const;

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
};

