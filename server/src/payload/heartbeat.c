#include "heartbeat.h"

void on_client_heartbeat_payload(const char* const payload_json) {
	char client_system_guid[MAX_SYSTEM_GUID_LENGTH];
	get_system_guid(client_system_guid, payload_json);

	struct Client* p_client = get_client(client_system_guid);

	if (p_client == NULL) {
		printf("Receieved heartbeat from non-existent client (%s)\n", client_system_guid);

		return;
	}

	update_client_heartbeat(p_client);
}