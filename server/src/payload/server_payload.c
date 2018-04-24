#include "server_payload.h"

int send_payload(const char* client_address, struct ServerPayloadOut payload) {
	SOCKET client_sock;
	if (init_client_socket(client_address, &client_sock))
		return 1;

	char* json_payload = json_serialize_to_string(payload.json_value_payload);

	char* buf = malloc(NET_BUFFER_SIZE);
	memset(buf, 0, NET_BUFFER_SIZE);
	memcpy(buf, &payload.payload_type, sizeof(payload.payload_type));
	memcpy(&(buf[4]), json_payload, strlen(json_payload));

	int bytes_sent = 0;
	while (bytes_sent < NET_BUFFER_SIZE) {
		int send_ret = send(client_sock, buf, NET_BUFFER_SIZE, 0);

		if (send_ret == SOCKET_ERROR) {
			printf("Failed to send client payload\n");

			break;
		}

		bytes_sent += send_ret;
	}

	json_free_serialized_string(json_payload);
	json_value_free(payload.json_value_payload);
	free(buf);
	closesocket(client_sock);

	return 0;
}