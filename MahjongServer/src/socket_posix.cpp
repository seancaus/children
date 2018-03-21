//
// Created by Ziv on 2018/3/20.
//
#include <iostream>
#include "socket.h"

#include "event.h"
#include "event2/listener.h"

using namespace std;

static void listener_cb(struct evconnlistener *, evutil_socket_t, struct sockaddr *, int socklen, void *);
static void listener_err_cb(struct evconnlistener *, void *);

Socket::Socket()
{
}

Socket::~Socket()
{
    event_base_free(_eventBase);
}

void Socket::listen(unsigned int port)
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    _eventBase = event_base_new();
    auto evconnlistener = evconnlistener_new_bind(_eventBase, listener_cb, (void*)this, LEV_OPT_REUSEABLE, -1, (struct sockaddr*)&sin, sizeof(sin));
    evconnlistener_set_error_cb(evconnlistener, listener_err_cb);

    event_base_dispatch(_eventBase);
//    event_new(_eventBase,)
//    event_add(nullptr, nullptr);
}


void listener_cb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *addr, int len, void *ptr)
{
    cout << "123456" << endl;
}

void listener_err_cb(struct evconnlistener *listener, void *ptr)
{

}