//
// Created by Ziv on 2018/4/1.
//
#include <iostream>
#include <uvw.hpp>

#include "Connector.h"

#include "Packet.h"
#include "MessageManager.h"

#include "table_generated.h"
#include "flatbuffers/minireflect.h"

using namespace std;
using namespace uvw;
using namespace ziv::hall::table;

Connector::Connector()
        :_loop(nullptr) {
    _packer = make_unique<Packet>();
    _msgManager = make_shared<MessageManager>();
}

Connector::~Connector() {

}

void Connector::connect(std::string &ip, unsigned port) {
    if (_loop) _loop->close();

    string data("");
    typedef std::function<void(const DataEvent &, TcpHandle &)> DataEventCallback;
    DataEventCallback dataEventCallback = std::bind(&Connector::onRecv, this, placeholders::_1, placeholders::_2, data);

    _loop = Loop::getDefault();
    _client = _loop->resource<uvw::TcpHandle>();
    _client->on<DataEvent>(dataEventCallback);
    _client->on<ErrorEvent>(std::bind(&Connector::onError,this,placeholders::_1, placeholders::_2));
    _client->on<ConnectEvent>(std::bind(&Connector::onConnect,this,placeholders::_1,placeholders::_2));
    _client->on<ShutdownEvent>(std::bind(&Connector::onShutdown,this,placeholders::_1, placeholders::_2));
    _client->on<CloseEvent>(std::bind(&Connector::onClose,this,placeholders::_1,placeholders::_2));
    _client->connect(ip, port);
}

void Connector::loop() {
    _loop->run();
}

void Connector::send(int packId, std::string &data) {
    string msg;
    _packer->pack(packId, data, msg);
    _client->write(const_cast<char*>(msg.data()), msg.length());
}

void Connector::onConnect(const uvw::ConnectEvent &event, uvw::TcpHandle &handle) {
    _client->read();

    flatbuffers::FlatBufferBuilder builder(1024);
    auto ctreq = CreateSetdownRequest(builder,builder.CreateString("test1234"));

    auto obj = CreateMessage(builder, Any_SetdownRequest, ctreq.Union());
    builder.Finish(obj);

    string str(reinterpret_cast<const char*>(builder.GetBufferPointer()),builder.GetSize());
    send(1, str);
}

void Connector::onRecv(const DataEvent &event, TcpHandle &, string &data) {
    data.append(event.data.get(), event.length);

    unsigned int packid;
    string msg;
    if( 0 == (packid = _packer->unpack(data, msg)) )return;

    _msgManager->pushMessage(packid, msg);
}

void Connector::onShutdown(const ShutdownEvent &event, TcpHandle &handle) {
    cout << "on server end" << endl;
//    handle.close();
}

void Connector::onClose(const CloseEvent &event, TcpHandle &handle) {
    cout << "on server close" << endl;
}

void Connector::onError(const uvw::ErrorEvent &event, uvw::TcpHandle &) {
    cout << event.name()<<":"<< event.what() << endl;
}