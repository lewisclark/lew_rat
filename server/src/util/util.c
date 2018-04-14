#include "util.h"

int get_system_guid(char* system_guid_out, const char* const payload_json) {
	JSON_Value* root_value = json_parse_string(payload_json);

	if (json_value_get_type(root_value) != JSONObject)
		return 1;

	JSON_Object* root_object = json_value_get_object(root_value);

	const char* system_guid = json_object_dotget_string(root_object, "system_guid");
	strcpy(system_guid_out, system_guid);

	json_value_free(root_value);

	return 0;
}