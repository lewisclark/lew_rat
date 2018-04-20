#ifndef CLIENT_H
#define CLIENT_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "util/parson.h"
#include "constants.h"
#include "payload/system.h"
#include "util/util.h"
#include "payload/server_payload.h"

struct Client {
	time_t last_heartbeat;
	unsigned long ip_addr;
	struct SystemInfo* p_system_info;
};

struct ClientElement {
	struct Client* p_client;
	struct ClientElement* p_client_element_next;
};

extern struct ClientElement* add_client(unsigned long ip_addr, struct SystemInfo* p_system_info);
extern void remove_client_element(const struct ClientElement* const p_client_element);
struct ClientElement* get_client_element(const struct Client* const p_client);
struct ClientElement* get_previous_client_element(const struct ClientElement* const p_client_element);

extern void client_loop(); // Check clients for timeout, etc.
extern struct Client* get_client(const char* const client_system_guid);
extern void convert_ip(char* ip_out, unsigned long long_ip);
extern void print_clients();
extern void update_client_heartbeat(struct Client* p_client);
int has_timed_out(struct Client* p_client);

#endif