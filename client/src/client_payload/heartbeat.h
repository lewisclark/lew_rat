#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include "util/parson.h"
#include "payload.h"
#include "networking/payload_type.h"
#include "util/util.h"
#include <windows.h>

extern void heartbeat_loop();
int send_heartbeat_payload();

#endif