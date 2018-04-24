#ifndef SERVER_PAYLOAD_CALLBACK_H
#define SERVER_PAYLOAD_CALLBACK_H

#include "payload/payload_type.h"

struct ClientPayloadIn {
	enum ClientPayloadInType payload_type;
	const char* payload_json;
	unsigned long ip_addr;
};

typedef int(__cdecl* ClientPayloadInCallback)(struct ClientPayloadIn payload_in);

extern int set_payload_callback(enum ClientPayloadInType payload_type, ClientPayloadInCallback callback);
extern ClientPayloadInCallback get_payload_callback(enum ClientPayloadInType payload_type);

#endif