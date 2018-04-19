//
// Created by Ziv on 2018/4/4.
//

#include <iostream>
#include "module/TableHandler.h"

#include "module/game/GameManager.h"
#include "module/table_generated.h"

using namespace std;
using namespace ziv::hall::table;

TableHandler::TableHandler() {
    _tableManager = make_shared<GameManager>();
}

TableHandler::~TableHandler()
{

}

void TableHandler::handleMessage(string &msg)
{
    auto object = GetMessage(msg.data());
    switch (object->object_type())
    {
        case Any_SetdownRequest :{
            auto message = object->object_as<SetdownRequest>();
            cout << message->playerId()->c_str() << endl;
            break;
        }
        default:
            break;
    }
}