//
// Created by Ziv on 2018/4/3.
//
#include "ConnectManager.h"
#include "flatbuffers/flatbuffers.h"
#include "module/hall_generated.h"
#include "network.h"

using namespace std;
using namespace share::hall;
using namespace flatbuffers;

static shared_ptr<ConnectManager> _root;

void login(const char* ca)
{
    _root = make_shared<ConnectManager>();
    _root->connect();

    flatbuffers::FlatBufferBuilder builder;
    LoginRequestBuilder requestBuilder(builder);
    requestBuilder.add_ca(builder.CreateString(ca));
    auto request = CreateMessage(builder,Any_LoginRequest,requestBuilder.Finish().Union());
    builder.Finish(request);
    string str(reinterpret_cast<const char*>(builder.GetBufferPointer()),builder.GetSize());

    _root->send(2, str);
}