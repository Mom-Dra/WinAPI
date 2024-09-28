#pragma once

#include "AStar.h"
#include "framework.h"

namespace MomDra
{
	class Rectangle
	{
	public:
		explicit Rectangle(int width, int height) noexcept;
		void Draw(const HDC& hdc) const noexcept;

	private:
		AStar::Node node;
		int width;
		int height;
	};
}

