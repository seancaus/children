//
// Created by Ziv on 2018/4/4.
//

#ifndef MAHJONGSERVER_TABLEMANAGER_H
#define MAHJONGSERVER_TABLEMANAGER_H

#include <memory>
#include <map>

using namespace std;

class TableManager {

public:
    TableManager();
    virtual ~TableManager();

protected:
    map<unsigned int, shared_ptr<int>> _tables;
};


#endif //MAHJONGSERVER_TABLEMANAGER_H
