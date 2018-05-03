//
// Created by Ziv on 2018/4/25.
//

#include <string>
#include "uuid.h"
#include "utils/uuid.h"


using namespace std;

std::string uuid::genUUID()
{
    uuid_t uuid;
    uuid_generate(uuid);

    char uid[100];
    uuid_unparse(uuid, uid);
    return string(uid);
}

