#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <stdlib.h>
#include <stdio.h>
#include "client/client.h"
#include "constants.h"
#include "util/util.h"
#include "payload/server_payload_callback.h"

extern int on_heartbeat_payload_received(struct ClientPayloadIn payload_in);

#endif