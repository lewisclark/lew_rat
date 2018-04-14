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

enum WindowsVersion {
	WINDOWSVERSION_UNKNOWN,
	WINDOWSVERSION_2000,
	WINDOWSVERSION_XP,
	WINDOWSVERSION_VISTA,
	WINDOWSVERSION_7,
	WINDOWSVERSION_8,
	WINDOWSVERSION_10,
	WINDOWSVERSION_SERVER
};

extern const char* WindowsVersionNames[];

struct SystemInfo {
	enum WindowsVersion windows_version;
	char* username;
	char* system_guid;
};

extern int process_system_data(const char* system_data, struct SystemInfo** pp_system_info_out);
int deserialize_system_data(const char* const system_data, struct SystemInfo* const p_system_info_out);
extern void free_system_info(struct SystemInfo* p_system_info);

#endif