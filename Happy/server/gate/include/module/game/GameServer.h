//
// Created by Ziv on 2018/4/19.
//

#ifndef GATE_GAMESERVER_H
#define GATE_GAMESERVER_H


class GameServer {


public:
    GameServer();
    virtual ~GameServer();

    virtual void join();
    virtual void leave();
    virtual bool enouth();

protected:

};


#endif //GATE_GAMESERVER_H
