#include "client.h"

struct ClientElement* p_client_element_head = NULL;

struct ClientElement* add_client(unsigned long ip_addr, struct SystemInfo* p_system_info) {
	// Check if this client already exists here

	struct Client* p_client = malloc(sizeof(struct Client));

	p_client->last_heartbeat = time(NULL);
	p_client->ip_addr = ip_addr;
	p_client->p_system_info = p_system_info;

	struct ClientElement* p_client_element = malloc(sizeof(struct ClientElement));

	p_client_element->p_client = p_client;
	p_client_element->p_client_element_next = p_client_element_head != NULL ? p_client_element_head : NULL;

	p_client_element_head = p_client_element;

	return p_client_element;
}

void remove_client_element(const struct ClientElement* const p_client_element) {
	struct ClientElement* p_previous_client_element = get_previous_client_element(p_client_element);

	if (p_previous_client_element == NULL) // We're removing the head of the list
		p_client_element_head = p_client_element->p_client_element_next;
	else
		p_previous_client_element->p_client_element_next = p_client_element->p_client_element_next;

	free_system_info(p_client_element->p_client->p_system_info);
	free((void*)p_client_element->p_client);
	free((void*)p_client_element);
}

void client_loop() {
	while (1) {
		struct ClientElement* cur_element = p_client_element_head;

		while (cur_element != NULL) {
			struct Client* p_client = cur_element->p_client;

			if (has_timed_out(p_client)) {
				printf("Client %s has timed out\n", p_client->p_system_info->system_guid);

				struct ClientElement* next_element = cur_element->p_client_element_next;
				remove_client_element(cur_element);
				cur_element = next_element;
				continue;
			}

			cur_element = cur_element->p_client_element_next;
		}

		print_clients();

		Sleep(2500);
	}
}

struct Client* get_client(const char* const client_system_guid) {
	struct ClientElement* cur_element = p_client_element_head;
	while (cur_element != NULL) {
		if (strcmp(cur_element->p_client->p_system_info->system_guid, client_system_guid) == 0)
			return cur_element->p_client;

		cur_element = cur_element->p_client_element_next;
	}

	return NULL;
}

void print_clients() {
	printf("\n\n----------[Connected clients]----------\n");

	int i = 0;
	struct ClientElement* cur_element = p_client_element_head;

	while (cur_element != NULL) {
		struct Client* p_client = cur_element->p_client;

		char ip[16];
		convert_ip(ip, p_client->ip_addr);

		printf("Client #%d\n", i);
		printf("\tIPv4 addr -> %s\n", ip);
		printf("\tUsername -> %s\n", p_client->p_system_info->username);
		printf("\tSystem GUID -> %s\n", p_client->p_system_info->system_guid);
		printf("\tSystem OS -> %s\n", WindowsVersionNames[p_client->p_system_info->windows_version]);
		printf("\tLast heartbeat -> %lu\n", (unsigned long)p_client->last_heartbeat);
		printf("\tHas timed out -> %s\n", has_timed_out(p_client) ? "true" : "false");

		cur_element = cur_element->p_client_element_next;
		i++;
	}

	printf("---------------------------------------\n\n");
}

struct ClientElement* get_client_element(const struct Client* const p_client) {
	struct ClientElement* cur_element = p_client_element_head;
	while (cur_element != NULL) {
		if (cur_element->p_client == p_client)
			return cur_element;

		cur_element = cur_element->p_client_element_next;
	}

	return NULL;
}

struct ClientElement* get_previous_client_element(const struct ClientElement* const p_client_element) {
	struct ClientElement* cur_element = p_client_element_head;
	while (cur_element != NULL) {
		if (cur_element->p_client_element_next == p_client_element)
			return cur_element;

		cur_element = cur_element->p_client_element_next;
	}

	return NULL;
}

void convert_ip(char* ip_out, unsigned long long_ip) {
	sprintf(ip_out, "%d.%d.%d.%d",
		long_ip & 0xFF, (long_ip >> 8) & 0xFF, (long_ip >> 16) & 0xFF, (long_ip >> 24) & 0xFF);
}

int has_timed_out(struct Client* p_client) {
	return (time(NULL) - p_client->last_heartbeat) > 10 ? 1 : 0;
}

void handle_heartbeat_payload(const char* const payload_json) {
	JSON_Value* root_value = json_parse_string(payload_json);

	if (json_value_get_type(root_value) != JSONObject) {
		printf("handle_heartbeat_payload failed\n");

		return;
	}

	JSON_Object* root_object = json_value_get_object(root_value);

	on_client_heartbeat(json_object_dotget_string(root_object, "system_guid"));

	json_value_free(root_value);
}

void on_client_heartbeat(const char* const client_system_guid) {
	struct Client* p_client = get_client(client_system_guid);

	if (p_client == NULL)
		return;

	p_client->last_heartbeat = time(NULL);
}