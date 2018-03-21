#include <iostream>
#include "socket.h"

using namespace std;

int main() {
    Socket socket;
    socket.listen(9999);
    cout << "Hello, World!" << endl;
    return 0;
}