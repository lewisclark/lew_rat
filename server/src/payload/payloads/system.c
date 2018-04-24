#include "system.h"

const char* WindowsVersionNames[] = {
	"Windows unknown",
	"Windows 2000",
	"Windows XP",
	"Windows Vista",
	"Windows 7",
	"Windows 8",
	"Windows 10",
	"Windows Server"
};

int on_system_payload_received(struct ClientPayloadIn payload_in) {
	struct SystemInfo* p_system_info = malloc(sizeof(struct SystemInfo));

	if (deserialize_system_data(payload_in.payload_json, p_system_info)) {
		printf("Failed to deserialize system json payload");

		return 1;
	}

	add_client(payload_in.ip_addr, p_system_info);

	return 0;
}

int deserialize_system_data(const char* payload_json, struct SystemInfo* const p_system_info_out) {
	JSON_Value* root_value = json_parse_string(payload_json);

	if (json_value_get_type(root_value) != JSONObject)
		return 1;

	JSON_Object* root_object = json_value_get_object(root_value);

	p_system_info_out->windows_version = (enum WindowsVersion)json_object_dotget_number(root_object, "payload.windows_version");
	const char* username = json_object_dotget_string(root_object, "payload.username");
	const char* system_guid = json_object_dotget_string(root_object, "payload.system_guid");

	// We need to strcpy because json_value_free below free's the strings from json_object_dotget_string
	p_system_info_out->username = malloc(UNLEN + 1);
	p_system_info_out->system_guid = malloc(MAX_SYSTEM_GUID_LENGTH);

	strcpy(p_system_info_out->username, username);
	strcpy(p_system_info_out->system_guid, system_guid);

	json_value_free(root_value);

	return 0;
}

void free_system_info(struct SystemInfo* p_system_info) {
	free(p_system_info->username);
	free(p_system_info->system_guid);
	free(p_system_info);
}