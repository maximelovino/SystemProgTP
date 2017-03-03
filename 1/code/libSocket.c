//
// Created by Lovino Maxime on 03.03.17.
//

#include "libSocket.h"

void io_loop(int input, int output) {
	char buffer[BUFF_SIZE];
	ssize_t nb_reads;

	while (1) {
		if (0 > (nb_reads = read(input, buffer, BUFF_SIZE))) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		if (0 > write(output, buffer, nb_reads)) {
			perror("write");
			exit(EXIT_FAILURE);
		}
	}
}


int socket_unix_client(int domain, int type, char* path) {
	int fdsock;
	struct sockaddr_un remote;
	remote.sun_family = domain;
	strcpy(remote.sun_path, path);

	if (0 > (fdsock = socket(domain, type, 0))) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	if (0 >
		connect(fdsock, (const struct sockaddr*) &remote, strlen(remote.sun_path) + sizeof(remote.sun_family) + 1)) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
	return fdsock;
}

int socket_unix_server(int domain, int type, char* path, unsigned int maxClients) {
	unlink(path);
	int fdsock;
	struct sockaddr_un remote;
	remote.sun_family = domain;
	strcpy(remote.sun_path, path);
	unsigned int remote_len = strlen(remote.sun_path) + sizeof(remote.sun_family) + 1;

	if (0 > (fdsock = socket(domain, type, 0))) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	if (0 > bind(fdsock, (struct sockaddr*) &remote, remote_len)) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
	if (0 > listen(fdsock, maxClients)) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	int new_socket = accept(fdsock, (struct sockaddr*) &remote, &remote_len);
	if (new_socket < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	return new_socket;
}

int socket_ip_server(int domain, int type, char* path, unsigned int maxClients, int port) {
	unlink(path);
	int fdsock;
	struct sockaddr_in addrInternet, addrClient;
	addrInternet.sin_family = domain;
	addrInternet.sin_addr.s_addr = htonl(INADDR_ANY);
	addrInternet.sin_port = (in_port_t) htons(port);

	if ((fdsock = socket(domain, type, 0)) < 0) {
		perror("Socket error");
		_exit(EXIT_FAILURE);
	}

	if (bind(fdsock, (struct sockaddr*) &addrInternet, sizeof(addrInternet)) < 0) {
		perror("Binding error");
		_exit(EXIT_FAILURE);
	}

	if (listen(fdsock, maxClients) < 0) {
		perror("Listen error");
		_exit(EXIT_FAILURE);
	}

	socklen_t clientLength;
	int newSocket = accept(fdsock, (struct sockaddr*) &addrClient, &clientLength);
	if (newSocket < 0) {
		perror("Accept error");
		_exit(EXIT_FAILURE);
	}
	return newSocket;
}

int socket_ip_client(int domain, int type, char* address, int port) {
	int fdsock;
	struct sockaddr_in remote;
	remote.sin_family = domain;
	remote.sin_addr.s_addr = inet_addr(address);
	remote.sin_port = (in_port_t) htons(port);

	if ((fdsock = socket(domain, type, 0)) < 0) {
		perror("Socket error");
		_exit(EXIT_FAILURE);
	}

	if (connect(fdsock, (const struct sockaddr*) &remote, sizeof(remote)) < 0) {
		perror("Connection error");
		_exit(EXIT_FAILURE);
	}
	return fdsock;
}