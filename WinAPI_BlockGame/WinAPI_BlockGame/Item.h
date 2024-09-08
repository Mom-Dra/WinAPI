#pragma once
class Item
{
public:
	enum class ItemType
	{
		INCREASEBALLCOUNT,
		ATTACHBALLTOBLOCK,
		RESIZEBLOCK
	};

	virtual ~Item() = default;
	virtual void Apply() = 0;

	ItemType GetType() const { return type; }

protected:
	ItemType type;
};

class IncreaseBallCount : public Item
{
public:
	inline constexpr explicit IncreaseBallCount() { type = ItemType::INCREASEBALLCOUNT; }
	void Apply() override
	{

	}
};

class AttachBallToBlock : public Item
{
public:
	inline constexpr explicit AttachBallToBlock() { type = ItemType::ATTACHBALLTOBLOCK; }
	void Apply() override
	{

	}
};

class ResizeBlock : public Item
{
public:
	inline constexpr explicit ResizeBlock() { type = ItemType::RESIZEBLOCK; }
	void Apply() override
	{

	}
};