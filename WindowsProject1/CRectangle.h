#pragma once
#include "CObject.h"
#include "framework.h"
#include <array>

class CRectangle : public CObject
{
private:
	std::array<POINT, 4> points;
	std::array<Vector2, 4> vPoints;
	int length;

public:
	inline explicit CRectangle(const Vector2& center, const int& speed, const int& length, const Vector2& moveDir);

	inline constexpr void Update(const float& deltaTime) override;
	inline void Draw(const HDC& hdc) const override;

private:
	inline void TranslateAndRotate(const Vector2& nV, float angle) override;
	inline constexpr void SetPoints(const Matrix3x3& m) override;
};

inline CRectangle::CRectangle(const Vector2& center, const int& speed, const int& length, const Vector2& moveDir) : CObject{ center, speed, moveDir, length / std::sqrt(2.0f) }, length{ length }
{
	float halfLength{ length / 2.0f };

	// vPoints도 설정해줘야 함
	// 왼쪽 위, 오른쪽 위, 오른쪽 아래, 왼쪽 아래
	vPoints[0].x = -halfLength;
	vPoints[0].y = -halfLength;

	vPoints[1].x = halfLength;
	vPoints[1].y = -halfLength;

	vPoints[2].x = halfLength;
	vPoints[2].y = halfLength;

	vPoints[3].x = -halfLength;
	vPoints[3].y = halfLength;

	transposeMatrix.SetTranslation(center);

	SetPoints(transposeMatrix);
}

inline constexpr void CRectangle::Update(const float& deltaTime)
{
	TranslateAndRotate(Vector2{ moveDir.x * speed * deltaTime,  moveDir.y * speed * deltaTime }, speed * deltaTime);
}

inline void CRectangle::Draw(const HDC& hdc) const
{
	Polygon(hdc, &points[0], 4);
}

inline void CRectangle::TranslateAndRotate(const Vector2& nV, float nAngle)
{
	SetCenter(center + nV);
	SetAngle(angle + nAngle);

	transposeMatrix.SetTranslationAndRotation(center, angle);

	SetPoints(transposeMatrix);
}

inline constexpr void CRectangle::SetPoints(const Matrix3x3& m)
{
	for (int i = 0; i < 4; ++i)
	{
		Vector2 nPoint = m * vPoints[i];

		points[i].x = static_cast<LONG>(nPoint.x);
		points[i].y = static_cast<LONG>(nPoint.y);
	}
}