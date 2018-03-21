#include <iostream>
#include <thread>
#include "socket.h"

using namespace std;

int main() {

    thread t([](){
        cout << "11111" << endl;
    });
//    t.join();

    Socket socket;
    socket.listen(9999);
    cout << "Hello, World!" << endl;
    return 0;
}