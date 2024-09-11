#include "MyRandom.h"

int MyRandom::GetRandomInt(int min, int max) noexcept
{
	if (min > max)
	{
		std::swap(min, max);
	}

	std::uniform_int_distribution<int> i_dis{ min, max };

	return i_dis(g);
}