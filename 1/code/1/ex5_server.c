//
// Created by Lovino Maxime on 03.03.17.
//

#include "../libSocket.h"

int main() {
	printf("Hello, I'll be the server\n");

	int fd = socket_ip_server(AF_INET, SOCK_STREAM, "/tmp/ipSocket", 10, 9876);
	int socket = waitForConnection(fd);
	printf("Server done\n");
	io_loop(socket, 1);
}