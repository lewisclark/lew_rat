#ifndef CLIENTNETWORKMESSAGETYPE_H
#define CLIENTNETWORKMESSAGETYPE_H

// Defines the types of information a client can send to the server

enum ClientPayloadType {
	CLIENTPAYLOADTYPE_SYSTEMINFO,
	CLIENTPAYLOADTYPE_HEARTBEAT
};

#endif
