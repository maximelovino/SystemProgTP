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
	printf("Hello, I'll be the receiver\n");
	struct sockaddr_un local;
	int s;
	unlink(SOCKETPATH);


	if ((s = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
		perror("socket error");

	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCKETPATH);

	int len = strlen(local.sun_path) + sizeof(local.sun_family);
	//len+1 otherwise last char truncated
	if (bind(s, (struct sockaddr*) &local, len + 1) < 0)
		perror("socket binding error");

	char buffer[1024];

	while (1) {
		memset(buffer, 0, 1024);
		read(s, buffer, 1024);
		if (strcmp(buffer, "exit\n") == 0) {
			printf("receiver quitting\n");
			break;
		}
		printf("%s", buffer);
	}
}