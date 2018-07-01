//
// Created by Ziv on 2018/3/26.
//
#include <memory>
#include <iostream>
#include "Application.h"
#include "utils/uuid.h"
#include "glog/logging.h"

using namespace std;

int main() {

    google::InitGoogleLogging("test");
    LOG(FATAL) << "Hello,GLOG!";
    google::ShutdownGoogleLogging();

    auto root = make_shared<Application>();
//    root->start();

    return 0;
}