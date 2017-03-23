//
// Created by Lovino Maxime on 02.03.17.
//

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKETPATH "/tmp/mysocket"

int main() {
	printf("Hello I'll be the sender\n");

	struct sockaddr_un remote;
	int s;


	if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
		perror("socket error");


	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCKETPATH);

	char buffer[1024];

	while (1) {
		memset(buffer, 0, 1024);
		read(STDIN_FILENO, buffer, 1024);
		if (sendto(s, buffer, 1024, 0, (struct sockaddr*) &remote, sizeof(struct sockaddr_un)) < 0)
			perror("send to error");
		if (strcmp(buffer, "exit\n") == 0) {
			printf("Exiting sender\n");
			break;
		}
	}
}