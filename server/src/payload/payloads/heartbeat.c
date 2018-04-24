#include "heartbeat.h"

int on_heartbeat_payload_received(struct ClientPayloadIn payload_in) {
	char client_system_guid[MAX_SYSTEM_GUID_LENGTH];
	get_system_guid(client_system_guid, payload_in.payload_json);

	struct Client* p_client = get_client(client_system_guid);

	if (p_client == NULL) {
		printf("Receieved heartbeat from non-existent client (%s)\n", client_system_guid);

		return 1;
	}

	update_client_heartbeat(p_client);

	return 0;
}