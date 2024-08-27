#include "CCircle.h"
#include "CObject.h"
#include "framework.h"

CCircle::CCircle(const POINT& center, const float& speed, const float& radius) : CObject{ center, speed }, radius{ radius }
{

}

void CCircle::Update()
{
}

void CCircle::Draw(const HDC& hdc) const
{
    Ellipse(hdc, center.x - radius, center.y + radius, center.x + radius, center.y - radius);
}

bool CCircle::Collision()
{
    return false;
}
