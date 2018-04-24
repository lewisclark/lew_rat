#ifndef SYSTEM_H
#define SYSTEM_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Lmcons.h>

#include "util/parson.h"
#include "constants.h"
#include "client/system_info.h"
#include "payload/server_payload_callback.h"
#include "client/client.h"

extern const char* WindowsVersionNames[];

extern int on_system_payload_received(struct ClientPayloadIn payload_in);
int deserialize_system_data(const char* payload_json, struct SystemInfo* const p_system_info_out);
extern void free_system_info(struct SystemInfo* p_system_info);

#endif