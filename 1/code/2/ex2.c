/*
Ecrire un programme qui crée n processus fils, n étant donné en
paramètre. Chaque processus fils est relié au père par une socketpair.
Les processus fils affichent leur numéro de PID sur la sortie standard (voir
l'appel système getpid(2)), puis l'écrivent dans une boucle infinie
vers le père, en espaçant les écritures d'un nombre de seconde aléatoire
entre 2 et 10 secondes (voir la fonction rand(3) et la fonction sleep(3)).
Après chaque écriture du pid dans la socketpair, le processus fils se mettra
en attente d'une réponse du père, qu'il affichera sur la sortie standard.
Le processus père devra surveiller l'ensemble des socketpairs en lecture
en utilisant l'appel système select(), puis renverra le pid reçu mis au carré
vers le fils de pid correspondant.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libSocket.h"

int main(int argc, const char* argv[]) {
	if (argc < 2) {
		printf("Usage ./2_ex2 <childrenCount>\n");
		_exit(1);
	}
	int count = atoi(argv[1]);
	int** sockets = malloc(count * sizeof(int*));
	printf("Count %i\n", count);
	printf("------------LAUNCHING CHILDRENS------------\n");
	for (int i = 0; i < count; ++i) {
		sockets[i] = malloc(2 * sizeof(int));
		int res = socketpair(AF_UNIX, SOCK_STREAM, 0, sockets[i]);
		if (res == -1) {
			perror("Error creating socket");
			_exit(1);
		} else {
			printf("Created socket for %i\n", i);
		}
		int pid = fork();
		if (pid == 0) {
			//We're in the son
			int newPID = getpid();
			printf("Hello, my PID is %i\n", newPID);
			while (1) {
				//loop for the son
			}
		}
	}
	//this is where the father will do its thing
	while (1) {}
}
