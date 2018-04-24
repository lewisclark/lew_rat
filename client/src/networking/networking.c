#include "networking.h"

int init_networking() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		WSACleanup();

		return 1;
	}

	set_payload_callback(SERVERPAYLOADTYPE_REQUESTSYSTEMINFO, on_system_payload_requested);

	send_system_info_payload();

	return 0;
}

void listen_on_socket() {
	SOCKET sock;
	while (init_listen_socket(&sock))
		Sleep(10000);

	struct sockaddr_in sockaddr_server;
	int addrlen = sizeof(struct sockaddr_in);

	while (1) {
		SOCKET socket_server = accept(sock, (struct sockaddr*)&sockaddr_server, &addrlen); // TODO: only allow SERVER_ADDRESS to connect to this socket

		if (socket_server != INVALID_SOCKET)
			on_connected_listen_socket(&socket_server);
	}
}

int init_socket(SOCKET* socket_out) {
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		log_message("init_socket - Failed to create socket\n");
		closesocket(sock);

		return 1;
	}

	struct sockaddr_in server; // Every piece of data in this struct must be stored network byte order
	inet_pton(AF_INET, SERVER_ADDRESS, &server.sin_addr);
	server.sin_family = AF_INET; // IPV4
	server.sin_port = htons(SERVER_LISTENING_PORT); // Make network byte order

	if (connect(sock, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
		log_message("init_socket - Failed to connect to server\n");
		closesocket(sock);

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
	sockaddr.sin_port = htons(CLIENT_LISTENING_PORT);

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

int on_connected_listen_socket(SOCKET* p_socket_server) {
	char* recv_buf = malloc(NET_BUFFER_SIZE);
	memset(recv_buf, 0, NET_BUFFER_SIZE);

	int bytes_recv = 0;
	int recv_ret;

	while ((recv_ret = recv(*p_socket_server, &(recv_buf[bytes_recv]), NET_BUFFER_SIZE - bytes_recv, 0)) != 0) {
		if (bytes_recv >= NET_BUFFER_SIZE)
			break;

		if (recv_ret == SOCKET_ERROR) {
			log_message("Failed to receive payload from server\n");
			free(recv_buf);
			closesocket(*p_socket_server);

			return 1;
		}

		bytes_recv += recv_ret;
	}

	enum ServerPayloadInType payload_type = (enum ServerPayloadInType)recv_buf[0];
	const char* payload_json = &(recv_buf[sizeof(payload_type)]);

	ServerPayloadInCallback callback = get_payload_callback(payload_type);

	struct ServerPayloadIn payload_in;
	payload_in.payload_type = payload_type;
	payload_in.payload_json = payload_json;

	callback(payload_in);

	closesocket(*p_socket_server);
	free(recv_buf);

	return 0;
}

int close_socket(SOCKET* sock) {
	if (closesocket(*sock) == SOCKET_ERROR) {
		log_message("Failed to close socket\n");

		return 1;
	}

	return 0;
}
