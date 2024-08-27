#pragma once
class CObject
{
protected:
	float speed;

public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool Collision() = 0;
};

