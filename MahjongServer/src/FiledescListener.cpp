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
    auto ev = event_new(_eventBase,fd,EV_READ|EV_PERSIST,[](int fd,short what,void*ptr){
        cout << "read" << endl;
    }, (char*)"EventRead");
    event_add(ev, nullptr);
}