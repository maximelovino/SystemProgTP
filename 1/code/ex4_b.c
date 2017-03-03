//
// Created by Lovino Maxime on 02.03.17.
//

#include "libSocket.h"

int main() {
	printf("Hello, I'll be the server\n");
	int pid = fork();


	if (pid == 0) {
		//We're in the son
		int socket = socket_unix_server(AF_UNIX, SOCK_STREAM, "/tmp/sock_client", 10);
		printf("Server client socket done in son");
		io_loop(0, socket);
	} else {
		//We're in the parent
		int socket = socket_unix_server(AF_UNIX, SOCK_STREAM, "/tmp/sock_server", 10);
		printf("Server server socket done in parent");
		io_loop(socket, 1);
	}
}

