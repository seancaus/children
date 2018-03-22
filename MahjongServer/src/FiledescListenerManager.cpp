//
// Created by huxf on 2018/3/22.
//

#include <iostream>
#include "FiledescListenerManager.h"
#include "FiledescListener.h"

using namespace std;

FiledescListenerManager::FiledescListenerManager() {
}

FiledescListenerManager::~FiledescListenerManager() {

}

void FiledescListenerManager::dispatchfd(int fd)
{
    int size = _listeners.size();
    if( size == 0 )
    {
        auto listener = make_shared<FiledescListener>();
        _listeners.push_back(listener);
    }

    _listeners[0]->pushfd(fd);

    if( 0 == size)
    {
        _listeners[0]->listen();
    }
}
