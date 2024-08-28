#include "CRectangle.h"
#include "Vector2.h"

CRectangle::CRectangle(const Vector2& center, const int& speed, const int& length, const Vector2& moveDir) : CObject{ center, speed, moveDir }, length{ length }
{
	float halfLength{ length / 2.0f };

	float left{ center.x - halfLength };
	float right{ center.x + halfLength };
	float up{ center.y - halfLength };
	float down{ center.y + halfLength };

	// vPoints도 설정해줘야 함

	// 왼쪽 위, 오른쪽 위, 오른쪽 아래, 왼쪽 아래
	points[0].x = static_cast<LONG>(left);
	points[0].y = static_cast<LONG>(up);

	points[1].x = static_cast<LONG>(right);
	points[1].y = static_cast<LONG>(up);

	points[2].x = static_cast<LONG>(right);
	points[2].y = static_cast<LONG>(down);

	points[3].x = static_cast<LONG>(left);
	points[3].y = static_cast<LONG>(down);
}

void CRectangle::Update(const float& deltaTime)
{
	TranslateAndRotate(Vector2{ moveDir.x * speed * deltaTime,  moveDir.y * speed * deltaTime }, speed * deltaTime);

	/*float halfLength{ length / 2.0f };

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

void CRectangle::TranslateAndRotate(const Vector2& nV, const float& angle)
{
	center += nV;
	transposeMatrix.SetTranslationAndRotation(nV, angle);

	for (int i = 0; i < 4; ++i)
	{
		vPoints[i] = transposeMatrix * vPoints[i];
		points[i].x = static_cast<LONG> (vPoints[i].x);
		points[i].y = static_cast<LONG> (vPoints[i].y);
	}
}
