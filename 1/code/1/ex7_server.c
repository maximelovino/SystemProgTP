//
// Created by Lovino Maxime on 03.03.17.
//

#include "dataStructEx7.h"
#include "../libSocket.h"


int main() {
	int sock = socket_ip_server(AF_INET, SOCK_STREAM, "/tmp/sock7", 10, 4242);
	int fd = waitForConnection(sock);
	struct data varReceived;
	read(fd, &varReceived, sizeof(struct data));
	write(1, &varReceived, sizeof(varReceived));

	/*
	 * With standard struct, it will display toto, with the other, same thing
	 *
	 * Normally, depending on the architecture, the second structure is the only certain way to display toto
	 * It will force memory arrangement in a certain way
	 */
}