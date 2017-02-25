//
// Created by Lovino Maxime on 25.02.17.
//

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>

int main(){
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
			printf("Luke Skywalker: %s\n", buffer);
			sleep(1);
			char timeout[] = "timeout";
			write(s[1],timeout,strlen(timeout));
		}
	} else {
		printf("Luke, I am your father\n");
		//We're in the parent
		while (1) {
			memset(buffer,0,1024);
			read(STDIN_FILENO, buffer, 1024);
			write(s[0], buffer, 1024);
			memset(buffer,0,1024);
			read(s[0], buffer, 1024);
			printf("Anakin Skywalker: %s\n", buffer);
		}
	}

	return 0;
}