//
// Created by Ziv on 2018/4/1.
//

#ifndef MAHJONGSERVER_MESSAGEHANDLER_H
#define MAHJONGSERVER_MESSAGEHANDLER_H

#include <string>

using namespace std;

class MessageHandler {

public:
    virtual void handleMessage(string& msg) = 0;
};


#endif //MAHJONGSERVER_MESSAGEHANDLER_H
