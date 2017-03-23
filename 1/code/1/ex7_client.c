//
// Created by Lovino Maxime on 03.03.17.
//

#include "dataStructEx7.h"
#include "../libSocket.h"

int main() {
	int fd = socket_ip_client(AF_INET, SOCK_STREAM, "127.0.0.1", 4242);
	struct data var;
	var.id = 10;
	strcpy(var.name, "toto");
	write(fd, &var, sizeof(var));
}