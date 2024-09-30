#include "GameManager.h"
#include "AStar.h"
#include <algorithm>
#include "framework.h"
#include "Square.h"

namespace MomDra
{
    GameManager& GameManager::GetInstance()
    {
        static GameManager instance;

        return instance;
    }

    void GameManager::Draw(const HDC& hdc) const noexcept
    {
        for (const Square& rec : squares)
        {
            rec.Draw(hdc);
        }
    }

    void GameManager::LBUTTONDOWN(int x, int y) noexcept
    {
        if (x > WINDOW_WIDTH || y > WINDOW_HEIGHT) return;

        int row{ y / RECTANGLE_HEIGHT };
        int col{ x / RECTANGLE_WIDTH };

        switch (count)
        {
        case 0:
            start = &squares[row * NUM_OF_COLS + col];
            start->SetState(Square::State::START);
            break;
        case 1:
            end = &squares[row * NUM_OF_COLS + col];
            end->SetState(Square::State::END);
            break;
        }

        ++count;
    }

    void GameManager::RBUTTONDOWN(int x, int y) noexcept
    {
        if (x > WINDOW_WIDTH || y > WINDOW_HEIGHT) return;

        int row{ y / RECTANGLE_HEIGHT };
        int col{ x / RECTANGLE_WIDTH };

        // º® ¼³Á¤
        if (squares[row * NUM_OF_COLS + col].GetState() == Square::State::NONE)
        {
            squares[row * NUM_OF_COLS + col].SetState(Square::State::WALL);
        }
    }

    GameManager::GameManager() noexcept
    {
        squares.reserve(NUM_OF_RECTANGLE);

        for (int i = 0; i < NUM_OF_ROWS; ++i)
        {
            for (int j = 0; j < NUM_OF_COLS; ++j)
            {
                squares.emplace_back(j, i, RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
            }
        }
    }

    void GameManager::Initialize() noexcept
    {

    }
}
