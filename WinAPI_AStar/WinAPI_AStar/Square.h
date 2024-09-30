#pragma once

#include "AStar.h"
#include "framework.h"

namespace MomDra
{
	class Square
	{
	public:
		enum class State
		{
			START, END, WALL, NONE
		};

		explicit Square(int x, int y, int width, int height) noexcept;
		void Draw(const HDC& hdc) const noexcept;

		void SetG(int g) noexcept;
		void SetH(int h) noexcept;
		void SetState(State state) noexcept;
		State GetState() const noexcept;

	private:
		AStar::Node node;
		int width;
		int height;
		
		State state{ State::NONE };

		static constexpr int stringPadding{ 5 };
	};
}

