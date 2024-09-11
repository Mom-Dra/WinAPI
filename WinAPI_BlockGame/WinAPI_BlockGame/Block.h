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
	explicit inline constexpr Block();
	explicit inline constexpr Block(const Vector2& center, float width, float height);

	inline constexpr void SetWidth(float width) noexcept;
	inline constexpr void SetHeight(float height) noexcept;

	inline constexpr float GetLeft() const;
	inline constexpr float GetRight() const;
	inline constexpr float GetTop() const;
	inline constexpr float GetBottom() const;

	inline constexpr void Init() noexcept override;
	inline void Draw(const HDC& hdc) const noexcept override;
	inline constexpr void Update(const float deltaTime) override;

	inline constexpr float GetWidth() const noexcept;
	inline constexpr float GetHeight() const noexcept;
};

inline constexpr Block::Block() : Block{ Vector2::Zero, 0.0f, 0.0f }
{

}

inline constexpr Block::Block(const Vector2& center, float width, float height) : Object{ center }, width{ width }, height{ height }
{

}

inline constexpr void Block::SetWidth(float width) noexcept
{
	this->width = width;
}

inline constexpr void Block::SetHeight(float height) noexcept
{
	this->height = height;
}

inline constexpr float Block::GetLeft() const
{
	return GetCenter().x - width / 2.0f;
}

inline constexpr float Block::GetRight() const
{
	return GetCenter().x + width / 2.0f;
}

inline constexpr float Block::GetTop() const
{
	return GetCenter().y - height / 2.0f;
}

inline constexpr float Block::GetBottom() const
{
	return GetCenter().y + height / 2.0f;
}

inline constexpr void Block::Init() noexcept
{

}

inline void Block::Draw(const HDC& hdc) const noexcept
{ 
	Rectangle(hdc, GetLeft(), GetTop(), GetRight(), GetBottom());
}

inline constexpr void Block::Update(const float deltaTime)
{
	
}

inline constexpr float Block::GetWidth() const noexcept
{
	return width;
}

inline constexpr float Block::GetHeight() const noexcept
{
	return height;
}
