#pragma once

#include "AStar.h"
#include "framework.h"

namespace MomDra
{
	class Square
	{
	public:
		explicit Square(int x, int y, int width, int height) noexcept;
		void Draw(const HDC& hdc) const noexcept;

	private:
		AStar::Node node;
		int width;
		int height;

		static constexpr int stringPadding{ 5 };
	};
}

