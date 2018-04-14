#include "heartbeat.h"

int send_heartbeat_payload() {
	struct Payload payload;
	payload.client_payload_type = CLIENTPAYLOADTYPE_HEARTBEAT;
	payload.json_value_payload = json_value_init_object();

	if (send_payload(payload))
		return 1;

	return 0;
}

void heartbeat_loop() {
	while (1) {
		if (send_heartbeat_payload())
			log_message("Failed to send heartbeat payload\n");

		Sleep(HEARTBEAT_FREQUENCY * 1000);
	}
}