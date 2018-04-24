#ifndef CLIENT_PAYLOAD_CALLBACK_H
#define CLIENT_PAYLOAD_CALLBACK_H

#include "payload/payload_type.h"

struct ServerPayloadIn {
	enum ServerPayloadInType payload_type;
	const char* payload_json;
};

typedef int(__cdecl* ServerPayloadInCallback)(struct ServerPayloadIn payload_in);

extern int set_payload_callback(enum ServerPayloadInType payload_type, ServerPayloadInCallback callback);
extern ServerPayloadInCallback get_payload_callback(enum ServerPayloadInType payload_type);

#endif