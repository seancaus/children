//
// Created by Ziv on 2018/4/4.
//

#ifndef MAHJONGSERVER_TABLEMANAGER_H
#define MAHJONGSERVER_TABLEMANAGER_H

#include <memory>
#include <map>
#include <string>

using namespace std;

class GameServer;

class GameManager {

public:
    GameManager();
    virtual ~GameManager();

    void join(int gameId, string tableId = "", int seat = 0);
    void leave(string tableId);

protected:
    shared_ptr<GameServer> createGameServer(int gameId);


protected:
    map<string, shared_ptr<GameServer>> _gservers;
};


#endif //MAHJONGSERVER_TABLEMANAGER_H
