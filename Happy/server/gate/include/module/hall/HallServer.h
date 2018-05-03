//
// Created by Ziv on 2018/4/26.
//

#ifndef GATESERVER_HALLSERVER_H
#define GATESERVER_HALLSERVER_H

#include <string>

namespace share {
    namespace hall {

        struct Message;

    }
}

class HallServer {

public:
    HallServer();

    void handleMessage(std::string& uid, std::string& msg);

protected:

    void onLogin(std::string& uid, const share::hall::Message*);

};


#endif //GATESERVER_HALLMANAGER_H
