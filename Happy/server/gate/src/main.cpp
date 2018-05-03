//
// Created by Ziv on 2018/3/26.
//
#include <memory>
#include <iostream>
#include "Root.h"
#include "uuid.h"

using namespace std;

int main() {

    auto root = make_shared<Root>();
    root->start();

    return 0;
}