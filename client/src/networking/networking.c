#include "networking.h"

int init_networking() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		WSACleanup();

		return 1;
	}

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)heartbeat_loop, NULL, 0, NULL);

	send_system_info_payload();

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

// TODO: Seperate file for heartbeat
int heartbeat() {
	//if (!send_payload(json_value_init_object(), CLIENTPAYLOADTYPE_HEARTBEAT))
		//return 1;

	return 0;
}

DWORD heartbeat_loop(void* param) {
	while (1) {
		heartbeat();

		Sleep(5000);
	}

	return 0;
}
