//
// Created by Ziv on 2018/4/1.
//

#ifndef NET_CONNECTOR_H
#define NET_CONNECTOR_H

#include <memory>

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
class MessageManager;

class Connector {

public:
    Connector() ;
    virtual ~Connector();

    void connect(std::string &ip, unsigned port);
    void loop();

    void send(int packId, std::string &data);

    void onConnect(const uvw::ConnectEvent &event, uvw::TcpHandle &handle);
    void onRecv(const uvw::DataEvent &event, uvw::TcpHandle &, string &data);
    void onShutdown(const uvw::ShutdownEvent &event, uvw::TcpHandle &handle);
    void onClose(const uvw::CloseEvent &event, uvw::TcpHandle &handle);
    void onError(const uvw::ErrorEvent &, uvw::TcpHandle &);


    const shared_ptr<MessageManager> &getMsgManager() const {
        return _msgManager;
    }

protected:

    shared_ptr<uvw::Loop>       _loop;
    shared_ptr<uvw::TcpHandle>  _client;
    unique_ptr<Packet>          _packer;

    shared_ptr<MessageManager> _msgManager;
};


#endif //NET_CONNECTOR_H
