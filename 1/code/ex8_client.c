//
// Created by Lovino Maxime on 04.03.17.
//

#include "libSocket.h"

int main() {
	int fd = socket_ip_client(AF_INET, SOCK_STREAM, "127.0.0.1", 4242);
	printf("We're connected\n");
	io_loopback(0, fd, 1);
}