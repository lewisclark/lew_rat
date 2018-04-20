#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SERVER_LISTENING_PORT 16778
#define CLIENT_LISTENING_PORT 16779
#define NET_BUFFER_SIZE 100000
#define MAX_NUM_CLIENTS 100

#define CLIENT_TIMEOUT_TIME 10 // Time (in seconds) before a client is marked as timed out if not sending heartbeats

#define MAX_SYSTEM_GUID_LENGTH 36 + 2 + 1 // GUID is 36 characters but {} is added to guid in get_system_guid. +1 null terminator

#endif