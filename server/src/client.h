#ifndef CLIENT_H
#define CLIENT_H

#include <time.h>
#include <stdlib.h>
#include "parson.h"
#include "constants.h"
#include "system.h"

// TODO: Seperate ClientElement list stuff?

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
extern struct Client* get_client(const char* const client_system_guid);
extern void print_clients();
struct ClientElement* get_client_element(const struct Client* const p_client);
struct ClientElement* get_previous_client_element(const struct ClientElement* const p_client_element);
extern void convert_ip(char* ip_out, unsigned long long_ip);
int has_timed_out(struct Client* p_client);
extern void handle_heartbeat_payload(const char* const payload_json);
void on_client_heartbeat(const char* const client_system_guid);

#endif