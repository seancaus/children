#include <iostream>
#include <thread>
#include <ConnectManager.h>
#include "TCPConnector.h"

#include "MessageManager.h"
#include "flatbuffers/minireflect.h"
#include "module/hall_generated.h"

using namespace std;
using namespace share::hall;
using namespace flatbuffers;

int main() {

    auto root = make_shared<ConnectManager>();
    root->connect("127.0.0.1", 9999);

    flatbuffers::FlatBufferBuilder builder;
    auto ca = builder.CreateString("1");
    LoginRequestBuilder requestBuilder(builder);
    requestBuilder.add_ca(ca);
    auto request = CreateMessage(builder,Any_LoginRequest,requestBuilder.Finish().Union());
    builder.Finish(request);
    string str(reinterpret_cast<const char*>(builder.GetBufferPointer()),builder.GetSize());
    root->send(2, str);

    root->start(true);

    cout << "main end" << endl;

    return 0;
}