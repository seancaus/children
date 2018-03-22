//
// Created by huxf on 2018/3/22.
//

#include <iostream>
#include "FiledescListener.h"

#include "event.h"
#include "event2/listener.h"

FiledescListener::FiledescListener() {
    _eventBase = event_base_new();
}

FiledescListener::~FiledescListener() {
    event_base_free(_eventBase);
}

void FiledescListener::listen() {
    _thread = make_shared<thread>([this](){
        event_base_dispatch(_eventBase);
    });
}

void FiledescListener::pushfd(int fd)
{
    cout << "fd:" << fd << endl;
    auto ev = bufferevent_socket_new(_eventBase,fd,0);
    bufferevent_setcb(ev,[](struct bufferevent *bev, void *ctx){

        size_t n = 0;
        char data[8192];
        while((n = bufferevent_read(bev,data, sizeof(data))) > 0){
            cout << data << endl;
            bufferevent_write(bev,data,n);
        };
        cout << "end" << endl;
    }, nullptr, nullptr, nullptr);
    cout << "ev:" << ev << endl;
    bufferevent_enable(ev,EV_READ);
}