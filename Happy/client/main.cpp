#include <iostream>
#include <thread>
#include <handler/TableHandler.h>
#include "Connector.h"

#include "MessageManager.h"
#include "table_generated.h"

using namespace std;
using namespace ziv::hall::table;

int main() {

    std::string ip("127.0.0.1");

    Connector conn;
    conn.connect(ip,9999);
    conn.getMsgManager()->registerListener(1,make_shared<TableHandler>());


    thread con([&conn](){conn.loop();});
    con.join();
    cout << "main end" << endl;

    return 0;
}