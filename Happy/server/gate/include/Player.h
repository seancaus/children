//
// Created by Ziv on 2018/4/22.
//

#ifndef GATESERVER_PLAYER_H
#define GATESERVER_PLAYER_H

#include <string>

class Player {

public:
    Player();
    virtual ~Player();

protected:

    int _id;
    std::string _nickName;

};


#endif //GATESERVER_PLAYER_H
