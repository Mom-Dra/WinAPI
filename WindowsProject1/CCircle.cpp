#include "CCircle.h"
#include "CObject.h"
#include "framework.h"

CCircle::CCircle(const Vector2& center, const int& speed, const int& radius, const Vector2& moveDir) : CObject{ center, speed, moveDir }, radius{ radius }
{

}

void CCircle::Update(const float& deltaTime)
{
    center.x += moveDir.x * speed * deltaTime;
    center.y += moveDir.y * speed * deltaTime;
}

void CCircle::Draw(const HDC& hdc) const
{
    Ellipse(hdc, static_cast<int>(center.x - radius), static_cast<int>(center.y + radius), static_cast<int>(center.x + radius), static_cast<int>(center.y - radius));
}

bool CCircle::Collision()
{
    return false;
}

void CCircle::TranslateAndRotate(const Vector2& nV, float angle)
{

}
