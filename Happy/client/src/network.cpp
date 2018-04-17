//
// Created by Ziv on 2018/4/3.
//
#include <Connector.h>
#include "network.h"

#include "table_generated.h"
#include "flatbuffers/minireflect.h"

using namespace ziv::hall::table;

static Connector connect;

void login(const char* playerName)
{
    std::string ip("127.0.0.1");
    connect.connect(ip, 9999);

}

void setdown() {
    flatbuffers::FlatBufferBuilder builder(1024);
    auto request = CreateSetdownRequest(builder,builder.CreateString("test001"));
    auto msg = CreateMessage(builder, Any_SetdownRequest, request.Union());
    builder.Finish(msg);

    string str(reinterpret_cast<const char*>(builder.GetBufferPointer()),builder.GetSize());
    connect.send(1,str);
}

