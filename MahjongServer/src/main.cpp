#include <iostream>

#include <memory>
#include "ConnectListener.h"

using namespace std;

int main() {

    auto listener = make_shared<ConnectListener>();
    listener->listen(9999);
    return 0;
}