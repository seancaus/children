//
// Created by Ziv on 2018/3/26.
//
#include <services/TableHandler.h>
#include "Server.h"
#include "MessageManager.h"

int main() {
    Server server;

    auto service = make_shared<TableHandler>();
    server.getServiceManager()->registerListener(1, service);

    server.start();
    return 0;
}