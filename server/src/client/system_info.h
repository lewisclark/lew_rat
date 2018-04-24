#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

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

struct SystemInfo {
	enum WindowsVersion windows_version;
	char* username;
	char* system_guid;
};

#endif