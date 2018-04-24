#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include "util/parson.h"
#include "payload/client_payload.h"
#include "payload/payload_type.h"
#include "util/util.h"
#include <windows.h>

extern void heartbeat_loop();
int send_heartbeat_payload();

#endif