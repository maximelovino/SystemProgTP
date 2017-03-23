//
// Created by Lovino Maxime on 03.03.17.
//

#include "../libSocket.h"

int main() {
	printf("Hello, I'll be the client\n");
	int pid = fork();

	if (pid == 0) {
		//We're in the son
		int socket = socket_unix_client(AF_UNIX, SOCK_STREAM, "/tmp/sock_client");
		printf("Client client socket done in son");
		io_loop(socket, 1);
	} else {
		//We're in the parent
		int socket = socket_unix_client(AF_UNIX, SOCK_STREAM, "/tmp/sock_server");
		printf("Client server socket done in parent");
		io_loop(0, socket);
	}
}