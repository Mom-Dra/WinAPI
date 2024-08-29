#include "Vector3.h"

constexpr Vector3 Vector3::UnitX{ 1.0f, 0.0f, 0.0f };
constexpr Vector3 Vector3::UnitY{ 0.0f, 1.0f, 0.0f };
constexpr Vector3 Vector3::UnitZ{ 0.0f, 0.0f, 1.0f };
constexpr Vector3 Vector3::One{ 1.0f, 1.0f, 1.0f };
constexpr Vector3 Vector3::Zero{ 0.0f, 0.0f, 0.0f };

//constexpr Vector3::Vector3() : Scalars{ std::array<float, Dimension>{ 0.0f, 0.0f , 0.0f } }
//{
//
//}
//
//constexpr Vector3::Vector3(const Vector2& InV, bool IsPoint) : x{ InV.x }, y{ InV.y }, z{ IsPoint ? 1.0f : 0.0f }
//{
//
//}
//
//constexpr Vector3::Vector3(float InX, float InY, float InZ) : x{ InX }, y{ InY }, z{ InZ }
//{
//
//}
//
//constexpr float Vector3::operator[](int index) const
//{
//	if (index < 0 || index >= Dimension)
//		throw std::out_of_range("Index out of range");
//
//	return Scalars[index];
//}
//
//constexpr float& Vector3::operator[](int index)
//{
//	if (index < 0 || index >= Dimension)
//		throw std::out_of_range("Index out of range");
//
//	return Scalars[index];
//}
//
//constexpr Vector3 Vector3::operator-() const
//{
//	return Vector3{ -x, -y, -z };
//}
//
//constexpr Vector3& Vector3::operator*=(float InScale)
//{
//	x *= InScale;
//	y *= InScale;
//	z *= InScale;
//
//	return *this;
//}
//
//constexpr Vector3& Vector3::operator/=(float InScale)
//{
//	x /= InScale;
//	y /= InScale;
//	z /= InScale;
//
//	return *this;
//}
//
//constexpr Vector3& Vector3::operator+=(const Vector3& InVector)
//{
//	x += InVector.x;
//	y += InVector.y;
//	z += InVector.z;
//
//	return *this;
//}
//
//constexpr Vector3& Vector3::operator-=(const Vector3& InVector)
//{
//	x -= InVector.x;
//	y -= InVector.y;
//	z -= InVector.z;
//
//	return *this;
//}
//
//constexpr float Vector3::Dot(const Vector3& InVector) const
//{
//	return x * InVector.x + y * InVector.y + z * InVector.z;
//}
//
//constexpr Vector2 Vector3::ToVector2() const
//{
//	return Vector2{ x, y };
//}
//
//constexpr Vector3 operator*(const Vector3& v, float InScale)
//{
//	return Vector3{ v.x * InScale, v.y * InScale, v.z * InScale };
//}
//
//constexpr Vector3 operator/(const Vector3& v, float InScale)
//{
//	return Vector3{ v.x / InScale, v.y / InScale, v.z / InScale };
//}
//
//constexpr Vector3 operator*(const Vector3& a, const Vector3& b)
//{
//	return Vector3{ a.x * b.x, a.y * b.y, a.z * b.z };
//}
//
//constexpr Vector3 operator+(const Vector3& a, const Vector3& b)
//{
//	return Vector3{ a.x + b.x, a.y + b.y, a.z + b.z };
//}
//
//constexpr Vector3 operator-(const Vector3& a, const Vector3& b)
//{
//	return Vector3{ a.x - b.x, a.y - b.y, a.z - b.z };
//}
//
//constexpr Vector3 Vector3::UnitX{ 1.0f, 0.0f, 0.0f };
//constexpr Vector3 Vector3::UnitY{ 0.0f, 1.0f, 0.0f };
//constexpr Vector3 Vector3::UnitZ{ 0.0f, 0.0f, 1.0f };
//constexpr Vector3 Vector3::One{ 1.0f, 1.0f, 1.0f };
//constexpr Vector3 Vector3::Zero{ 0.0f, 0.0f, 0.0f };