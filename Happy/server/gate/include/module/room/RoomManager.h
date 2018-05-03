//
// Created by Ziv on 2018/4/22.
//

#ifndef GATESERVER_ROOMMANAGER_H
#define GATESERVER_ROOMMANAGER_H

#include <string>

class RoomManager {
public:
    void join(int gameId, std::string tableId = "", int seat = 0);
    void leave(std::string tableId);
};


#endif //GATESERVER_ROOMMANAGER_H
