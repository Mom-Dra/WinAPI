#include "Vector3.h"
#include "Matrix3x3.h"

constexpr Matrix3x3 Matrix3x3::Identity{ Vector3{1.0f, 0.0f, 0.0f}, Vector3{0.0f, 1.0f, 0.0f}, Vector3{0.0f, 0.0f, 1.0f} };
