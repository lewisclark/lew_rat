#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <stdlib.h>
#include <stdio.h>
#include "client/client.h"
#include "constants.h"
#include "util/util.h"

extern void on_client_heartbeat_payload(const char* const payload_json);

#endif