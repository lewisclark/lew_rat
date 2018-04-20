#include "networking.h"

int init_networking() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		WSACleanup();

		return 1;
	}
	
	SOCKET sock;
	if (init_listen_socket(&sock) != 0) {
		printf("Failed to set up/bind socket, aborting...\n");

		return 1;
	}

	struct sockaddr_in sockaddr_client;
	int addrlen = sizeof(struct sockaddr_in);

	while (1) {
		SOCKET socket_client = accept(sock, (struct sockaddr*)&sockaddr_client, &addrlen); // TODO: only allow SERVER_ADDRESS to connect to this socket

		if (socket_client != INVALID_SOCKET)
			on_client_connected(&socket_client, sockaddr_client);
	}

	return 0;
}

int init_listen_socket(SOCKET* socket_out) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		WSACleanup();
		closesocket(sock);

		return 2;
	}

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.S_un.S_addr = INADDR_ANY;
	server.sin_port = htons(SERVER_LISTENING_PORT);

	if (bind(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		WSACleanup();
		closesocket(sock);

		return 3;
	}

	if (listen(sock, 3) == SOCKET_ERROR) {
		WSACleanup();
		closesocket(sock);

		return 4;
	}

	*socket_out = sock;

	return 0;
}

int init_client_socket(const char* client_address, SOCKET* socket_out) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		printf("Failed to create socket for client\n");
		closesocket(sock);

		return 1;
	}

	struct sockaddr_in sockaddr_client;
	inet_pton(AF_INET, client_address, &sockaddr_client.sin_addr);
	sockaddr_client.sin_family = AF_INET;
	sockaddr_client.sin_port = htons(CLIENT_LISTENING_PORT);

	if (connect(sock, (struct sockaddr*)&sockaddr_client, sizeof(sockaddr_client)) == SOCKET_ERROR) {
		printf("Failed to connect to client socket\n");
		closesocket(sock);

		return 1;
	}

	*socket_out = sock;

	return 0;
}

int on_client_connected(SOCKET* p_socket_client, struct sockaddr_in client_addr) {
	//printf("Connection from client %d\n", client_addr.sin_addr.S_un.S_addr);

	char* recv_buf = malloc(NET_BUFFER_SIZE);
	memset(recv_buf, 0, NET_BUFFER_SIZE);

	int bytes_recv = 0;
	int recv_ret;

	while ((recv_ret = recv(*p_socket_client, &(recv_buf[bytes_recv]), NET_BUFFER_SIZE - bytes_recv, 0)) != 0) {
		if (bytes_recv >= NET_BUFFER_SIZE)
			break;

		if (recv_ret == SOCKET_ERROR) {
			printf("Failed to receive payload - %d\n", WSAGetLastError());
			free(recv_buf);

			return 1;
		}

		bytes_recv += recv_ret;

		//printf("\nReceived part of %d bytes. We have received %d in total, we need %d bytes more.\n",
			//recv_ret, bytes_recv, NET_BUFFER_SIZE - bytes_recv);
	}

	enum ClientPayloadType payload_type = (enum ClientPayloadType)recv_buf[0];
	handle_client_network_message(payload_type, &(recv_buf[sizeof(payload_type)]), client_addr);

	closesocket(*p_socket_client);
	free(recv_buf);

	//printf("Disconnected client %d\n", *p_socket_client);

	return 0;
}

int handle_client_network_message(enum ClientPayloadType payload_type, const char* const payload_json, struct sockaddr_in client_addr) {
	switch (payload_type) {
	case CLIENTPAYLOADTYPE_SYSTEMINFO:
	{
		struct SystemInfo* p_system_info;
		on_client_system_payload(payload_json, &p_system_info);

		add_client(client_addr.sin_addr.S_un.S_addr, p_system_info);

		break;
	}
	case CLIENTPAYLOADTYPE_HEARTBEAT:
		on_client_heartbeat_payload(payload_json);

		break;
	default:
		printf("Unhandled client payload type: %d\n", payload_type);

		break;
	}

	printf("\n\n%s\n\n", payload_json);

	return 0;
}