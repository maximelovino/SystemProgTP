//
// Created by Lovino Maxime on 03.03.17.
//

#ifndef CODE_LIBSOCKET_H
#define CODE_LIBSOCKET_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>


#define BUFF_SIZE 1024

/**
 *
 * @param input The file descriptor of the input socket
 * @param output The file descriptor of the output socket
 */
void io_loop(int input, int output);

/**
 * Function that return a socket descriptor for a client
 * @param domain The domain of the socket, as defined in sys/socket.h
 * @param type	The type of socket, as defined in sys/socket.h
 * @param path	The path of the socket on the fileSystem
 * @return	A file descriptor for the socket
 */
int socket_unix_client(int domain, int type, char* path);


/**
 * Function that return a socket descriptor for a server
 * @param domain The domain of the socket, as defined in sys/socket.h
 * @param type	The type of socket, as defined in sys/socket.h
 * @param path	The path of the socket on the fileSystem
 * @param maxClients The maximum number of clients connected
 * @return	A file descriptor for the socket
 */
int socket_unix_server(int domain, int type, char* path, unsigned int maxClients);

/**
 * Server socket creation
 * @param domain The domain of the socket
 * @param type The type of the socket
 * @param path The path of the socket on the filesystem
 * @param maxClients The maximum number of clients connections
 * @param port The port the socket listens on
 * @return The file descriptor of the socket
 */
int socket_ip_server(int domain, int type, char* path, unsigned int maxClients, int port);

/**
 * Client connection to an ip socket
 * @param domain The domain of the socket to connect to
 * @param type The type of socket to connect to
 * @param address The address of the socket
 * @param port The port of the socket
 * @return The socket file descriptor
 */
int socket_ip_client(int domain, int type, char* address, int port);

#endif //CODE_LIBSOCKET_H
