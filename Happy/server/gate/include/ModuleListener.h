//
// Created by Ziv on 2018/4/1.
//

#ifndef MAHJONGSERVER_MESSAGESERVICE_H
#define MAHJONGSERVER_MESSAGESERVICE_H

#include <string>

class ModuleListener {

public:
    virtual void handleMessage(std::string& uid, std::string& msg) = 0;
};


#endif //MAHJONGSERVER_MESSAGESERVICE_H
