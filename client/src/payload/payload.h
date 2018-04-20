#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "util/parson.h"
#include "networking/networking.h"
#include "networking/payload_type.h"

struct Payload {
	enum ClientPayloadType client_payload_type;
	JSON_Value* json_value_payload;
};

extern int send_payload(struct Payload payload);
void attach_system_guid(JSON_Value* json_value_payload);

#endif
