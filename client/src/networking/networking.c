#include "networking.h"

int init_networking() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		WSACleanup();

		return 1;
	}

	SOCKET sock;
	while (init_listen_socket(&sock))
		Sleep(10000);

	struct sockaddr_in server;
	int addrlen = sizeof(struct sockaddr_in);
	SOCKET socket_server;

	// FIX: If INVALID_SOCKET is produced here, it'll break the loop and die
	while ((socket_server = accept(sock, (struct sockaddr*)&server, &addrlen)) != INVALID_SOCKET) // TODO: only allow SERVER_ADDRESS to connect to this socket
		on_connected_listen_socket(&socket_server, server);

	//send_system_info_payload();

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

int init_listen_socket(SOCKET* socket_out) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		closesocket(sock);

		return 1;
	}

	struct sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.S_un.S_addr = INADDR_ANY;
	sockaddr.sin_port = htons(SERVER_PORT);

	if (bind(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == SOCKET_ERROR) {
		closesocket(sock);

		return 2;
	}

	if (listen(sock, 3) == SOCKET_ERROR) {
		closesocket(sock);

		return 3;
	}

	*socket_out = sock;

	return 0;
}

int on_connected_listen_socket(SOCKET* p_socket_server, struct sockaddr_in sockaddr_server) {
	return 0;
}

int close_socket(SOCKET* sock) {
	if (closesocket(*sock) == SOCKET_ERROR) {
		log_message("Failed to close socket\n");

		return 1;
	}

	return 0;
}
