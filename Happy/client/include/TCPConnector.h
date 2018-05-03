//
// Created by Ziv on 2018/4/1.
//

#ifndef NET_TCPCONNECTOR_H
#define NET_TCPCONNECTOR_H

#include <memory>
#include <string>
#include <vector>
#include <functional>

#include "IConnector.h"

using namespace std;

namespace uvw{
    class Loop;
    class TcpHandle;

    struct ErrorEvent;
    struct DataEvent;
    struct ListenEvent;
    struct ConnectEvent;
    struct ShutdownEvent;
    struct CloseEvent;
}

class Packet;

typedef std::function<void(unsigned int msgId, std::string&)> ReceiveHandler;

class TCPConnector : public IConnector{

public:
    TCPConnector(std::string ip, unsigned int port);
    virtual ~TCPConnector();

    virtual void connect()override;
    virtual void close() override;
    virtual void send(std::string &msg) override;
    virtual void receive() override;

    void loop();
    void send(int msgId, std::string &data);
    void onConnect(const uvw::ConnectEvent &event, uvw::TcpHandle &handle);
    void onRecv(const uvw::DataEvent &event, uvw::TcpHandle &, string &data);
    void onShutdown(const uvw::ShutdownEvent &event, uvw::TcpHandle &handle);
    void onClose(const uvw::CloseEvent &event, uvw::TcpHandle &handle);
    void onError(const uvw::ErrorEvent &, uvw::TcpHandle &);

    void set_handler(const ReceiveHandler &_handler);

protected:
    void clearCacheMsg();

protected:

    std::string     _ip;
    unsigned int    _port;

    bool                            _connected;
    shared_ptr<uvw::Loop>           _loop;
    shared_ptr<uvw::TcpHandle>      _client;
    unique_ptr<Packet>              _packer;
    vector<std::string>             _cacheMsgs;

    ReceiveHandler                  _receiveHandler;
};

#endif //NET_CONNECTOR_H
