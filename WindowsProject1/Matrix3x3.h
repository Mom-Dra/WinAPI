#pragma once

#include <array>
#include "Vector3.h"
#include "Vector2.h"

class Matrix3x3
{
public:
	explicit Matrix3x3();
	explicit constexpr Matrix3x3(const Vector3& InCol0, const Vector3& InCol1, const Vector3& InCol2);

	constexpr const Vector3& operator[](int index) const;
	constexpr Vector3& operator[](int index);
	friend constexpr Matrix3x3 operator*(const Matrix3x3& m, float InScalar);
	friend constexpr Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b);
	friend constexpr Vector3 operator*(const Matrix3x3& m, const Vector3& InVector);
	friend constexpr Vector2 operator*(const Matrix3x3& m, const Vector2& InVector);

	constexpr Matrix3x3 Transpose() const;
	constexpr void SetTranslation(const Vector2& nV);
	void SetRotation(const float& angle);
	void SetTranslationAndRotation(const Vector2& nV, const float& angle);

	//static constexpr Matrix3x3 Translation(float tx, float ty);

	static const Matrix3x3 Identity;
	static constexpr int Rank{ 3 };

	std::array<Vector3, Rank> Cols;
};

