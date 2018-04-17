//
// Created by Ziv on 2018/4/6.
//
#include <iostream>
#include "handler/TableHandler.h"

#include "table_generated.h"

using namespace std;
using namespace ziv::hall::table;

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