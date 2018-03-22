//
// Created by Ziv on 2018/3/22.
//

#ifndef MAHJONGSERVER_FILEDESCLISTENERMANAGER_H
#define MAHJONGSERVER_FILEDESCLISTENERMANAGER_H


#include <vector>
#include "FiledescListener.h"

class FiledescListenerManager {

public:
    FiledescListenerManager();
    virtual ~FiledescListenerManager();

    void dispatchfd(int fd);

protected:
    vector<shared_ptr<FiledescListener>>_listeners;

};


#endif //MAHJONGSERVER_FILEDESCLISTENERMANAGER_H
