#include "Matrix3x3.h"
#include <numbers>

Matrix3x3::Matrix3x3() : arr{ std::array<float, 3>{1, 0 ,0}, std::array<float, 3>{0, 1 ,0}, std::array<float, 3>{0, 0, 1} }
{

}

Matrix3x3::Matrix3x3(const std::array<std::array<float, 3>, 3>& initValues) : arr{ initValues }
{

}

void Matrix3x3::SetRotationX(const float& angle)
{
	float radianAngle{ angle * std::numbers::pi_v<float> / 180.0f };
}
