#pragma once
#include "CObject.h"

class CCircle : public CObject
{
private:
	float radius;

public:
	void Update() override;
	void Draw() override;
	bool Collision() override;
};

