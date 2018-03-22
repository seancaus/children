//
// Created by Ziv on 2018/3/22.
//

#ifndef MAHJONGSERVER_FILEDESCLISTENER_H
#define MAHJONGSERVER_FILEDESCLISTENER_H

#include <thread>

using namespace std;

class FiledescListener {

public:
    FiledescListener() ;
    virtual ~FiledescListener() ;

    void listen();
    void pushfd(int fd);

protected:

    struct event_base *_eventBase;
    shared_ptr<thread> _thread;
};


#endif //MAHJONGSERVER_FILEDESCLISTENER_H
