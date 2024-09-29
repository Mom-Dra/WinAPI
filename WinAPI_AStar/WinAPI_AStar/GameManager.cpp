#include "GameManager.h"
#include "AStar.h"
#include <algorithm>
#include "framework.h"
#include "Rectangle.h"

namespace MomDra
{
    GameManager& GameManager::GetInstance()
    {
        static GameManager instance;

        return instance;
    }

    void GameManager::Draw(const HDC& hdc) const noexcept
    {
        for (const Square& rec : rectangles)
        {
            rec.Draw(hdc);
        }
    }

    GameManager::GameManager() noexcept
    {
        rectangles.reserve(NUM_OF_RECTANGLE);

        for (int i = 0; i < NUM_OF_ROWS; ++i)
        {
            for (int j = 0; j < NUM_OF_COLS; ++j)
            {
                rectangles.emplace_back(i, j, RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
            }
        }
    }
}
