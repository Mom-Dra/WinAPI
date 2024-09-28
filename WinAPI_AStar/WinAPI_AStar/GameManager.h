#pragma once
#include "AStar.h"
#include <vector>
#include "Rectangle.h"
#include "framework.h"

namespace MomDra
{
	class GameManager
	{
	public:
		static GameManager& GetInstance();

		// ȭ�� ũ��
		static constexpr int WINDOW_WIDTH{ 800 };
		static constexpr int WINDOW_HEIGHT{ 800 };

		// Grid ��� ���� ����
		static constexpr int NUM_OF_ROWS{ 10 };
		static constexpr int NUM_OF_COLS{ 10 };
		
		// �簢���� ������
		static constexpr int NUM_OF_RECTANGLE{ NUM_OF_ROWS * NUM_OF_COLS };
		static constexpr int RECTANGLE_WIDTH{ WINDOW_WIDTH / NUM_OF_ROWS };
		static constexpr int RECTANGLE_HEIGHT{ WINDOW_HEIGHT / NUM_OF_COLS };

		void Draw(const HDC& hdc) const noexcept;

	private:
		explicit GameManager() noexcept;

		std::vector<MomDra::Rectangle> rectangles;
	};
}
