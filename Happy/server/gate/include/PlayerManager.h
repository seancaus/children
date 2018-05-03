//
// Created by Ziv on 2018/4/22.
//

#ifndef GATESERVER_PLAYERMANAGER_H
#define GATESERVER_PLAYERMANAGER_H

#include <map>
#include "Singleton.h"

class Player;

class PlayerManager : public Singleton<PlayerManager>{

protected:
    std::map<int,Player> onlinePlayers;
};


#endif //GATESERVER_PLAYERMANAGER_H
