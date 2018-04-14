#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SERVER_PORT 16778
#define CLIENT_BUFFER_SIZE 100000
#define MAX_NUM_CLIENTS 100

#define MAX_SYSTEM_GUID_LENGTH 36 + 2 + 1 // GUID is 36 characters but {} is added to guid in get_system_guid. +1 null terminator

#endif