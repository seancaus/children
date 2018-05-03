//
// Created by Ziv on 2018/4/1.
//
#include <iostream>
#include <uvw.hpp>
#include <fstream>

#include "TCPConnector.h"

#include "Packet.h"
#include "MessageManager.h"

#include "flatbuffers/minireflect.h"
#include "module/hall_generated.h"

using namespace share::hall;
using namespace flatbuffers;

using namespace std;
using namespace uvw;

TCPConnector::TCPConnector(string ip, unsigned int port):
        _ip(ip)
        ,_port(port)
        ,_loop(nullptr)
        , _connected(false)
        ,_receiveHandler(nullptr)
{
    _packer = make_unique<Packet>();
}

TCPConnector::~TCPConnector()
{
}

void TCPConnector::connect()
{
    if (_loop) _loop->close();

    string data("");
    typedef std::function<void(const DataEvent &, TcpHandle &)> DataEventCallback;
    DataEventCallback dataEventCallback = std::bind(&TCPConnector::onRecv, this, placeholders::_1, placeholders::_2, data);

    _loop = Loop::getDefault();
    _client = _loop->resource<uvw::TcpHandle>();
    _client->on<DataEvent>(dataEventCallback);
    _client->on<ErrorEvent>(std::bind(&TCPConnector::onError,this,placeholders::_1, placeholders::_2));
    _client->on<ConnectEvent>(std::bind(&TCPConnector::onConnect,this,placeholders::_1,placeholders::_2));
    _client->on<ShutdownEvent>(std::bind(&TCPConnector::onShutdown,this,placeholders::_1, placeholders::_2));
    _client->on<CloseEvent>(std::bind(&TCPConnector::onClose,this,placeholders::_1,placeholders::_2));
    _client->connect(_ip, _port);
}

void TCPConnector::close() {
    if (_loop) _loop->close();
}

void TCPConnector::send(std::string &msg) {
    if(_connected)
    {
        _client->write(const_cast<char*>(msg.c_str()), msg.length());
    } else
    {
//        ofstream of("c.txt",std::ios::binary);
//        of.write(msg.data(),msg.length());
        _cacheMsgs.push_back(msg);
    }
}

void TCPConnector::receive() {

}

void TCPConnector::loop()
{
    _loop->run();
}

void TCPConnector::send(int msgId, std::string &data)
{
    string msg;
    _packer->pack(msgId, data, msg);

    if(_connected)
    {
        _client->write(const_cast<char*>(msg.c_str()), msg.length());
    } else
    {
//        ofstream of("c.txt",std::ios::binary);
//        of.write(msg.data(),msg.length());
        _cacheMsgs.push_back(msg);
    }
}

void TCPConnector::onConnect(const uvw::ConnectEvent &event, uvw::TcpHandle &handle)
{
    _connected = true;

    _client->read();
    clearCacheMsg();

//    flatbuffers::FlatBufferBuilder builder;
//    auto ca = builder.CreateString("1");
//    LoginRequestBuilder requestBuilder(builder);
//    requestBuilder.add_ca(ca);
//    auto request = CreateMessage(builder,Any_LoginRequest,requestBuilder.Finish().Union());
//    builder.Finish(request);
//    string str(reinterpret_cast<const char*>(builder.GetBufferPointer()),builder.GetSize());
//    send(2, str);

}

void TCPConnector::onRecv(const DataEvent &event, TcpHandle &, string &data)
{
    data.append(event.data.get(), event.length);

    unsigned int msgId;
    string msg;
    if( -1 == (msgId = _packer->unpack(data, msg)) )return;

    if( !_receiveHandler )
    {
        cout << "_receiveHandler is nullptr" << endl;
        return;
    }

    _receiveHandler(msgId, msg);
}

void TCPConnector::onShutdown(const ShutdownEvent &event, TcpHandle &handle)
{
    cout << "on server end" << endl;
//    handle.close();
}

void TCPConnector::onClose(const CloseEvent &event, TcpHandle &handle)
{
    cout << "on server close" << endl;
}

void TCPConnector::onError(const uvw::ErrorEvent &event, uvw::TcpHandle &)
{
    cout << event.name()<<":"<< event.what() << endl;
}

void TCPConnector::clearCacheMsg()
{
    while( !_cacheMsgs.empty() )
    {
        auto msg = _cacheMsgs.erase(_cacheMsgs.begin());
        ofstream of("s.txt",std::ios::binary);
        of.write((*msg).c_str(),(*msg).length());
        _client->write(const_cast<char*>((*msg).data()), (*msg).length());
    }
}

void TCPConnector::set_handler(const ReceiveHandler &_handler)
{
    _receiveHandler = _handler;
}