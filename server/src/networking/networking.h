#ifndef NETWORKING_H
#define NETWORKING_H

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <ws2tcpip.h>
#include "constants.h"
#include "system.h"
#include "client_payload_type.h"
#include "client.h"

#pragma comment(lib, "ws2_32.lib")

extern int init_networking();
extern int init_socket(SOCKET* socket_out);
extern int on_client_connected(SOCKET* socket_client, struct sockaddr_in client_addr);
extern int handle_client_network_message(enum ClientPayloadType message_type, const char* const payload_json, struct sockaddr_in client_addr);

#endif