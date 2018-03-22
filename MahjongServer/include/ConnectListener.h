//
// Created by Ziv on 2018/3/22.
//

#ifndef MAHJONGSERVER_CONNECTLISTENER_H
#define MAHJONGSERVER_CONNECTLISTENER_H

#include <memory>
#include <thread>

using namespace std;

class FiledescListenerManager;

class ConnectListener
{

public:
    ConnectListener() ;
    virtual ~ConnectListener() ;

    void listen(unsigned int port);
    void loop();

protected:

    shared_ptr<thread>_listener;
    struct event_base *_eventBase;
    struct evconnlistener* _evconnlistener;
    shared_ptr<FiledescListenerManager> _fdListenerManager;
};

#endif //MAHJONGSERVER_CONNECTLISTENER_H
