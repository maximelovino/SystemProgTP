//
// Created by Lovino Maxime on 04.03.17.
//

#include "libSocket.h"

int main() {
	printf("Welcome to the server\n");
	int socket = socket_ip_server(AF_INET, SOCK_STREAM, "/tmp/sock8v4", 10, 4242);
	printf("Socket created, waiting for connection\n");
	while (1) {
		int fd = waitForConnection(socket);

		int pid = fork();

		if (pid == 0) {
			//We're in the son, the socket connection is here
			printf("New connection\n");
			io_loop(fd, fd);
		} else {
			//We're in the parent, we're gonna keep listening for incoming
			printf("We're gonna listen for the next one\n");
		}
	}
}