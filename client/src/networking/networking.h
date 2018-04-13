#ifndef NETWORKING_H
#define NETWORKING_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include "constants.h"
#include "client_payload_type.h"
#include "util.h"
#include "parson.h"
#include "system.h"

extern int init_networking();
extern int send_log_file_contents(SOCKET* sock);
int init_socket(SOCKET* socket_out);
int close_socket(SOCKET* sock);
int heartbeat();
extern int send_payload(JSON_Value* root_value, enum ClientPayloadType payload_type);
DWORD heartbeat_loop(void* param);

#endif