//
// Created by Lovino Maxime on 03.03.17.
//

#include "libSocket.h"

int main() {
	printf("Hello, I'll be the client\n");
	int socket = socket_ip_client(AF_INET, SOCK_STREAM, "127.0.0.1", 9876);
	printf("Client done\n");
	io_loop(0, socket);

}