#include "client_payload_callback.h"

ServerPayloadInCallback callbacks[SERVERPAYLOADTYPE_COUNT];

int set_payload_callback(enum ServerPayloadInType payload_type, ServerPayloadInCallback callback) {
	callbacks[payload_type] = callback;

	return 0;
}

ServerPayloadInCallback get_payload_callback(enum ServerPayloadInType payload_type) {
	// Bounds checking?

	return callbacks[payload_type];
}