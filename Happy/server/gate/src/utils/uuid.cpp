//
// Created by Ziv on 2018/4/25.
//

#include <string>
#include <iostream>
#include "uuid/uuid.h"
#include "utils/uuid.h"

using namespace std;

std::string uuid::genUUID()
{
    size_t n;
    uuid_rc_t rc;
    uuid_t *uuid;
    void *vp = nullptr;

    if ((rc = uuid_create(&uuid)) != UUID_RC_OK)
        cout << uuid_error(rc) << endl;

    if ((rc = uuid_make(uuid, UUID_MAKE_V1)) != UUID_RC_OK)
        cout << uuid_error(rc) << endl;

    if ((rc = uuid_export(uuid, UUID_FMT_STR, &vp, &n)) != UUID_RC_OK)
        cout << uuid_error(rc) << endl;

    auto id = string((char*)vp);
    free(vp);

    uuid_destroy(uuid);
    return id;
}

