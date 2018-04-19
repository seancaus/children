//
// Created by Ziv on 2018/4/4.
//

#include "module/game/GameManager.h"


GameManager::GameManager() {

}

GameManager::~GameManager() {

}

void GameManager::join(int gameId, string tableId, int seat) {
    if (tableId.empty())
    {
        
    }
}

void GameManager::leave(string tableId) {

}

shared_ptr<GameServer> GameManager::createGameServer(int gameId) {
    return __1::shared_ptr<GameServer>();
}

