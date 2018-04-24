#ifndef SYSTEM_H
#define SYSTEM_H

#define WIN32_LEAN_AND_MEAN
#define MAX_SYSTEM_GUID_LENGTH 36 + 2 + 1 // GUID is 36 characters but {} is added to guid in get_system_guid. +1 null term

#include <windows.h>
#include <Lmcons.h>
#include <stdlib.h>
#include "util/parson.h"
#include "constants.h"
#include "util/util.h"
#include "payload/client_payload.h"

enum WindowsVersion {
	WINDOWSVERSION_UNKNOWN,
	WINDOWSVERSION_2000,
	WINDOWSVERSION_XP,
	WINDOWSVERSION_VISTA,
	WINDOWSVERSION_7,
	WINDOWSVERSION_8,
	WINDOWSVERSION_10,
	WINDOWSVERSION_SERVER,
	WINDOWSVERSION_COUNT
};

struct SystemInfo {
	enum WindowsVersion windows_version;
	char* username;
	char* system_guid;
};

extern int send_system_info_payload();
JSON_Value* serialize_system_info(const struct SystemInfo* const system_info);
enum WindowsVersion get_windows_version();
struct SystemInfo* get_system_info();
char* get_username();
void free_system_info(struct SystemInfo* p_system_info);
char* get_system_guid();

#endif
