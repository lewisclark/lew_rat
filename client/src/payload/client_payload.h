#ifndef PAYLOAD_H
#define PAYLOAD_H

#include "util/parson.h"
#include "networking/networking.h"
#include "payload/payload_type.h"

struct ClientPayloadOut {
	enum ClientPayloadOutType payload_type;
	JSON_Value* json_value_payload;
};

extern int send_payload(struct ClientPayloadOut payload);
void attach_system_guid(JSON_Value* json_value_payload);

#endif
