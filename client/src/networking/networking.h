#ifndef NETWORKING_H
#define NETWORKING_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include "constants.h"
#include "util/util.h"
#include "payload/payloads/system.h"

#pragma comment(lib, "ws2_32.lib")

extern int init_networking();
extern int init_socket(SOCKET* socket_out);
extern int init_listen_socket(SOCKET* socket_out);
extern int close_socket(SOCKET* sock);
extern int on_connected_listen_socket(SOCKET* p_socket_server, struct sockaddr_in sockaddr_server);
extern void listen_on_socket();

#endif
