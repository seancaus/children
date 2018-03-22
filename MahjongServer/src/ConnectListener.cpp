//
// Created by huxf on 2018/3/22.
//
#include <iostream>
#include <thread>

#include "ConnectListener.h"
#include "FiledescListenerManager.h"

#include "event.h"
#include "event2/listener.h"

using namespace std;
using namespace std::placeholders;

ConnectListener::ConnectListener()
{
    _fdListenerManager = make_shared<FiledescListenerManager>();
}

ConnectListener::~ConnectListener()
{
    evconnlistener_free(_evconnlistener);
    event_base_free(_eventBase);
}

void ConnectListener::listen(unsigned int port)
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;

    _eventBase = event_base_new();
//    evconnlistener_cb cb = (evconnlistener_cb)std::bind(&ConnectListener::connectcb,this);
    _evconnlistener = evconnlistener_new_bind(_eventBase, [](struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int len, void *ptr){
        auto fdlistenerManager = (FiledescListenerManager*)ptr;
        fdlistenerManager->dispatchfd(fd);
    }, (void*)_fdListenerManager.get(), LEV_OPT_REUSEABLE, -1, (struct sockaddr*)&sin, sizeof(sin));
    evconnlistener_set_error_cb(_evconnlistener, [](struct evconnlistener *, void *){
        cout << "evconnlistener_error" << endl;
    });
    _listener = make_shared<thread>(&ConnectListener::loop, this);
    _listener->join();
}

void ConnectListener::loop()
{
    event_base_dispatch(_eventBase);
}
