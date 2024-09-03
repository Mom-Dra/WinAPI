#pragma once
#include "framework.h"
#include "Object.h"
#include "Vector2.h"

class Block : public Object
{
private:
	float width;
	float height;

public:
	explicit inline constexpr Block(const Vector2& center, float width, float height);

	inline constexpr float GetLeft() const;
	inline constexpr float GetRight() const;
	inline constexpr float GetTop() const;
	inline constexpr float GetBottom() const;

	inline constexpr void Init() override;
	inline void Draw(const HDC& hdc) const override;
	inline constexpr void Update(const float deltaTime) override;
};

inline constexpr Block::Block(const Vector2& center, float width, float height) : Object{ center }, width{ width }, height{ height }
{

}

inline constexpr float Block::GetLeft() const
{
	return GetCenter().x - width / 2;
}

inline constexpr float Block::GetRight() const
{
	return GetCenter().x + width / 2;
}

inline constexpr float Block::GetTop() const
{
	return GetCenter().y - height / 2;
}

inline constexpr float Block::GetBottom() const
{
	return GetCenter().y + height / 2;
}

inline constexpr void Block::Init()
{

}

inline void Block::Draw(const HDC& hdc) const
{ 
	Rectangle(hdc, GetLeft(), GetTop(), GetRight(), GetBottom());
}

inline constexpr void Block::Update(const float deltaTime)
{

}
