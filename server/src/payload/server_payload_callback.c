#include "server_payload_callback.h"

ClientPayloadInCallback callbacks[CLIENTPAYLOADTYPE_COUNT];

int set_payload_callback(enum ClientPayloadType payload_type, ClientPayloadInCallback callback) {
	callbacks[payload_type] = callback;

	return 0;
}

ClientPayloadInCallback get_payload_callback(enum ClientPayloadType payload_type) {
	// Bounds checking?

	return callbacks[payload_type];
}