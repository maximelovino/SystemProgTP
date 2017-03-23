#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


/*
Ecrire la fonction C void block_unblock(int fd). Cette fonction
aura le comportement d'un interrupteur sur la valeur du flag
O_NONBLOCK d'un descripteur de fichier donné en paramètre : si
le flag est posé, elle le met à zéro, si le flag n'est pas
posé, elle le pose. Votre fonction devra vérifier que l'appel
à fcntl a bien réussi, sinon elle affichera une erreur sur
l'erreur standard avec perror().
 */

void block_unblock(int fd) {
	int flag = fcntl(fd, F_GETFL);

	if (flag == -1) {
		perror("File status error\n");
		_exit(1);
	}
	printf("Old flag %i\n", flag);
	int newFlags = flag ^O_NONBLOCK;
	printf("New flag %i\n", newFlags);
	if (fcntl(fd, F_SETFL, newFlags) == -1) {
		perror("File status setting error\n");
		_exit(1);
	} else {
		printf("Setting file successful\n");
	}
}


int main() {
	printf("Hello world\n");
	//FILE* test = fopen("testFile","rw+");
	int fd = open("../2/testFile", O_WRONLY);
	printf("opened file\n");
	printf("Got fd %i\n", fd);
	block_unblock(fd);
	printf("Done, bye\n");
}