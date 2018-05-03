//
// Created by Ziv on 2018/4/22.
//

#ifndef GATESERVER_ROOMHANDLER_H
#define GATESERVER_ROOMHANDLER_H

#include <string>
#include "ModuleListener.h"

class RoomHandler : public ModuleListener{

public:


    virtual void handleMessage(std::string &uid, std::string &msg) override ;


};


#endif //GATESERVER_ROOMHANDLER_H
