#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "util/parson.h"
#include "networking/networking.h"
#include "payload/payload_type.h"

struct ServerPayload {
	enum ServerPayloadType server_payload_type;
	JSON_Value* json_value_payload;
};

extern int send_payload(const char* client_address, struct ServerPayload payload);

#endif
