#ifndef SERVER_PAYLOAD_CALLBACK_H
#define SERVER_PAYLOAD_CALLBACK_H

#include "payload/payload_type.h"

struct ClientPayloadIn {
	enum ClientPayloadType payload_type;
	const char* payload_json;
};

typedef int(__cdecl* ClientPayloadInCallback)(struct ClientPayloadIn payload_in);

extern int set_payload_callback(enum ClientPayloadType payload_type, ClientPayloadInCallback callback);
extern ClientPayloadInCallback get_payload_callback(enum ClientPayloadType payload_type);

#endif