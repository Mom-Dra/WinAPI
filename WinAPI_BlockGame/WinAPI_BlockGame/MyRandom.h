#pragma once
#include <random>
#include <algorithm>

class MyRandom
{
private:
	inline static std::random_device rd;
	inline static std::default_random_engine g{ rd() };

	explicit inline constexpr MyRandom() noexcept = default;

public:
	static int GetRandomInt(int min, int max) noexcept;
};