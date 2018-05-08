#ifndef NETWORKING_H
#define NETWORKING_H

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "payload/payload_type.h"
#include "client/client.h"

#include "payload/server_payload_callback.h"
#include "payload/payloads/system.h"
#include "payload/payloads/heartbeat.h"

#pragma comment(lib, "ws2_32.lib")

extern int init_networking();
extern int init_listen_socket(SOCKET* socket_out);
extern int on_client_connected(SOCKET* socket_client, struct sockaddr_in client_addr);

extern int init_client_socket(const char* client_address, SOCKET* socket_out);

#endif
