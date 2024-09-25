#include "GameManager.h"
#include "AStar.h"

GameManager& GameManager::GetInstance()
{
    static GameManager instance;

    return instance;
}

void GameManager::Draw(const AStar& aStar) const noexcept
{




}
