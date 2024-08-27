#pragma once

#include <array>

class Matrix3x3
{
private:
	std::array<std::array<float, 3>, 3> arr;

public:
	explicit Matrix3x3();
	explicit Matrix3x3(const std::array<std::array<float, 3>, 3>& initValues);

	void SetRotationX(const float& angle);
};

