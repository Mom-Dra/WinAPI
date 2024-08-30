#include "CRectangle.h"
#include "Vector2.h"

CRectangle::CRectangle(const Vector2& center, const int& speed, const int& length, const Vector2& moveDir) : CObject{ center, speed, moveDir }, length{ length }
{
	float halfLength{ length / 2.0f };

	//float left{ center.x - halfLength };
	//float right{ center.x + halfLength };
	//float up{ center.y - halfLength };
	//float down{ center.y + halfLength };

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

void CRectangle::Update(const float& deltaTime)
{
	TranslateAndRotate(Vector2{ moveDir.x * speed * deltaTime,  moveDir.y * speed * deltaTime }, speed * deltaTime);

	/*center.x += moveDir.x * speed * deltaTime;
	center.y += moveDir.y * speed * deltaTime;

	float halfLength{ length / 2.0f };

	float left{ center.x - halfLength };
	float right{ center.x + halfLength };
	float up{ center.y - halfLength };
	float down{ center.y + halfLength };

	points[0].x = static_cast<LONG>(left);
	points[0].y = static_cast<LONG>(up);

	points[1].x = static_cast<LONG>(right);
	points[1].y = static_cast<LONG>(up);

	points[2].x = static_cast<LONG>(right);
	points[2].y = static_cast<LONG>(down);

	points[3].x = static_cast<LONG>(left);
	points[3].y = static_cast<LONG>(down);*/
}

void CRectangle::Draw(const HDC& hdc) const
{
	Polygon(hdc, &points[0], 4);
}

bool CRectangle::Collision()
{
	return false;
}

void CRectangle::TranslateAndRotate(const Vector2& nV, float nAngle)
{
	SetCenter(center + nV);
	SetAngle(angle + nAngle);

	transposeMatrix.SetTranslationAndRotation(center, angle);

	SetPoints(transposeMatrix);
}

void CRectangle::SetPoints(const Matrix3x3& m)
{
	for (int i = 0; i < 4; ++i)
	{
		Vector2 nPoint = m * vPoints[i];

		points[i].x = static_cast<LONG>(nPoint.x);
		points[i].y = static_cast<LONG>(nPoint.y);
	}
}
