#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main() {
	int s[2];
	int res = socketpair(AF_UNIX, SOCK_STREAM, 0, s);

	if (res == -1) {
		fprintf(stderr, "There was a problem creating the socket");
		_Exit(1);
	}else{
		fprintf(stderr, "Socket created\n");
	}

	int pid = fork();
	char buffer[1024];

	if (pid == 0) {
		printf("Hi I'm Luke\n");
		//We're in the child
		while (1) {
			memset(buffer,0,1024);
			read(s[1], buffer, 1024);
			printf("%s\n", buffer);
		}
	} else {
		printf("Luke, I am your father\n");
		//We're in the parent
		while (1) {
			memset(buffer,0,1024);
			read(STDIN_FILENO, buffer, 1024);
			write(s[0], buffer, 1024);
		}
	}

	return 0;
}