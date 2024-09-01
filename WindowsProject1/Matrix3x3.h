#pragma once

#include <array>
#include <numbers>
#include <stdexcept>
#include <cmath>
#include "Vector3.h"
#include "Vector2.h"

class Matrix3x3
{
public:
	static constexpr int Rank{ 3 };
	static const Matrix3x3 Identity;
	std::array<Vector3, Rank> Cols;

public:
	inline explicit constexpr Matrix3x3(const Vector3& InCol0, const Vector3& InCol1, const Vector3& InCol2);

	inline constexpr const Vector3& operator[](int index) const;
	inline constexpr Vector3& operator[](int index);
	inline friend constexpr Matrix3x3 operator*(const Matrix3x3& m, float InScalar);
	inline friend constexpr Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b);
	inline friend constexpr Vector3 operator*(const Matrix3x3& m, const Vector3& InVector);
	inline friend constexpr Vector2 operator*(const Matrix3x3& m, const Vector2& InVector);

	inline constexpr Matrix3x3 Transpose() const;
	inline constexpr void SetTranslation(const Vector2& nV);
	inline void SetRotation(const float& angle);
	inline void SetTranslationAndRotation(const Vector2& nV, const float& angle);
};

inline constexpr Matrix3x3::Matrix3x3(const Vector3& InCol0, const Vector3& InCol1, const Vector3& InCol2) : Cols{ InCol0, InCol1, InCol2 }
{

}

inline constexpr const Vector3& Matrix3x3::operator[](int index) const
{
	if (index < 0 || index >= Rank)
		throw std::out_of_range("Index out of range");

	return Cols[index];
}

inline constexpr Vector3& Matrix3x3::operator[](int index)
{
	if (index < 0 || index >= Rank)
		throw std::out_of_range("Index out of range");

	return Cols[index];
}

inline constexpr Matrix3x3 Matrix3x3::Transpose() const
{
	return Matrix3x3{ Vector3{Cols[0].x , Cols[1].x, Cols[2].x}, Vector3{Cols[0].y, Cols[1].y, Cols[2].y}, Vector3{Cols[0].z, Cols[1].z, Cols[2].z} };
}

inline constexpr void Matrix3x3::SetTranslation(const Vector2& nV)
{
	*this = Matrix3x3::Identity;

	Cols[2].x = nV.x;
	Cols[2].y = nV.y;
}

inline constexpr Matrix3x3 operator*(const Matrix3x3& m, float InScalar)
{
	return Matrix3x3{ m.Cols[0] * InScalar, m.Cols[1] * InScalar, m.Cols[2] * InScalar };
}

inline constexpr Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b)
{
	Matrix3x3 transposedMatrix{ a.Transpose() };
	return Matrix3x3{
		Vector3{transposedMatrix[0].Dot(b[0]), transposedMatrix[1].Dot(b[0]), transposedMatrix[2].Dot(b[0])},
		Vector3{transposedMatrix[0].Dot(b[1]), transposedMatrix[1].Dot(b[1]), transposedMatrix[2].Dot(b[1])},
		Vector3{transposedMatrix[0].Dot(b[2]), transposedMatrix[1].Dot(b[2]), transposedMatrix[2].Dot(b[2])}
	};
}

inline constexpr Vector3 operator*(const Matrix3x3& m, const Vector3& InVector)
{
	Matrix3x3 transposedMatrix{ m.Transpose() };
	return Vector3{ transposedMatrix[0].Dot(InVector), transposedMatrix[1].Dot(InVector), transposedMatrix[2].Dot(InVector) };
}

inline constexpr Vector2 operator*(const Matrix3x3& m, const Vector2& InVector)
{
	Vector3 v3{ InVector };
	v3 = m * v3;
	return v3.ToVector2();
}

inline void Matrix3x3::SetRotation(const float& angle)
{
	*this = Matrix3x3::Identity;

	float radian{ angle * std::numbers::pi_v<float> / 180.0f };

	float cosTheta{ std::cos(radian) };
	float sinTheta{ std::sin(radian) };

	Cols[0].x = cosTheta;
	Cols[0].y = sinTheta;

	Cols[1].x = -sinTheta;
	Cols[1].y = cosTheta;
}

inline void Matrix3x3::SetTranslationAndRotation(const Vector2& nV, const float& angle)
{
	*this = Matrix3x3::Identity;

	Cols[2].x = nV.x;
	Cols[2].y = nV.y;

	float radian{ angle * std::numbers::pi_v<float> / 180.0f };

	float cosTheta{ std::cos(radian) };
	float sinTheta{ std::sin(radian) };

	Cols[0].x = cosTheta;
	Cols[0].y = sinTheta;

	Cols[1].x = -sinTheta;
	Cols[1].y = cosTheta;
}