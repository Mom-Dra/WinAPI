#pragma once
#include "AStar.h"
#include <vector>
#include "framework.h"
#include "Square.h"

namespace MomDra
{
	class GameManager
	{
	public:
		static GameManager& GetInstance();

		// FPS
		static constexpr int FPS{ 60 };
		static constexpr float DELTATIME{ 1.0f / FPS };

		// 화면 크기
		static constexpr int WINDOW_WIDTH{ 800 };
		static constexpr int WINDOW_HEIGHT{ 800 };
		static constexpr int WINDOW_WIDTH_PADDING{ 200 };
		static constexpr int WINDOW_HEIGHT_PADDING{ 200 };

		// Grid 행과 열의 개수
		static constexpr int NUM_OF_ROWS{ 10 };
		static constexpr int NUM_OF_COLS{ 10 };

		// 사각형의 사이즈
		static constexpr int NUM_OF_RECTANGLE{ NUM_OF_ROWS * NUM_OF_COLS };
		static constexpr int RECTANGLE_WIDTH{ WINDOW_WIDTH / NUM_OF_ROWS };
		static constexpr int RECTANGLE_HEIGHT{ WINDOW_HEIGHT / NUM_OF_COLS };

		// Timer
		static constexpr int WM_TIMER_1{ 1 };

		void Draw(const HDC& hdc) const noexcept;
		void LBUTTONDOWN(int x, int y) noexcept;
		void RBUTTONDOWN(int x, int y) noexcept;

	private:
		explicit GameManager() noexcept;
		void Initialize() noexcept;

		std::vector<MomDra::Square> squares;

		Square* start{ nullptr };
		Square* end{ nullptr };
		int count{ 0 };
	};
}
