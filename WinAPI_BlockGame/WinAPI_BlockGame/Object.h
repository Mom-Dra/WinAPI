#pragma once
#include "framework.h"
#include "Vector2.h"

class Object
{
private:
	Vector2 center;

public:
	inline constexpr explicit Object(const Vector2& center);

	inline constexpr Vector2 GetCenter() const noexcept;
	inline constexpr void SetCenter(const Vector2& center) noexcept;

	inline constexpr virtual void Init() noexcept = 0;
	inline virtual void Draw(const HDC& hdc) const noexcept = 0;
	inline constexpr virtual void Update(const float deltaTime) = 0;

	virtual ~Object() = default;
};

inline constexpr Object::Object(const Vector2& center) : center{ center }
{

}

inline constexpr Vector2 Object::GetCenter() const noexcept
{
	return center;
}

inline constexpr void Object::SetCenter(const Vector2& center) noexcept
{
	this->center = center;
}
