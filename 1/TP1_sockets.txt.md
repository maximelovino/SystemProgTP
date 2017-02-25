Question 1 :
============

écrire un programme qui crée deux processus reliés 
par une paire de sockets (utiliser l'appel système socketpair). 
Les deux processus utilisent la socketpair pour communiquer 
de manière unidirectionnelle :

* Le processus père lit tout ce qui vient de l'entrée
  standard et l'écrit dans la socketpair. 
     
* Le processus fils lit tout ce qui vient de la socketpair
  et l'affiche sur la sortie standard. 

Question 2 :
============

Modifier le le programme de la question pour que les deux
processus utilisent la socketpair pour communiquer bidirectionnellement :

* Le processus père effectue continuellement et alternativement le traitement suivant :
  il lit tout ce qui vient de l'entrée standard et l'écrit dans la socketpair, 
  puis Il lit aussi tout ce qui vient de la socketpair et l'affiche sur
  la sortie standard.

* Le processus fils effectue continuellement et alternativement le traitement suivant :
  il lit tout ce qui vient de la socketpair et l'affiche sur la sortie standard puis 
  il écrit aussi la chaine "timeout" une fois par seconde dans la socket pair.

Afin de distinguer le père du fils qui écrivent en même temps sur le terminal d'exécution 
vous préfixerez  toutes les écritures sur la sortie standard de la chaine "pere:" 
pour indiquer que c'est  le pere qui écrit sur la sortie standard , et "fils:" pour 
indiquer que c'est le fils  qui écrit sur la sortie standard.

Assurez vous que votre programme est correct puis exécutez de la manière
suivante : redirigez le code source C de votre de votre programme dans l'entrée
standard du processus exécutant votre programme. 

Que constatez vous ?
 
Expliquer pourquoi la vitesse d'affichage du fils autant que celle du père
est limitée à une chaine de caractère par seconde ?

Décrire précisement un cas où ce programme peut s'inter-bloquer. Indice : 
Décrire ce qui se passe si c'est le fils qui est traité en premier ou bien
si c'est le père qui l'est par l'ordonnanceur.


Question 3:
===========

L'appel système socketpair() offre un service de communication FIFO bidirectionnel
entre deux processus issus d'un processus ancêtre ayant effectué l'appel système
socketpair. A l'inverse de la question 2, on veut à présent faire communiquer des 
processus qui n'ont pas forcément un ancêtre commun ayant appelé socketpair().

Répartir votre programme de la question 1 en deux programmes appelés "emetteur" et
"recepteur", créant chacun une socket de la famille AF_UNIX et de type de lien SOCK_STREAM 
de manière indépendante.

* L'émetteur lit tout ce qui vient de l'entrée standard et l'écrit dans la socket.

* Le récepteur lit tout ce qui vient de la socket et l'affche sur la sortie standard.

Que se passe-t-il si l'émetteur est exécuté avant le récepteur ?

Question 4:
===========

Effectuez la même séparation en programme récepteur/émetteur décrite en question 3, sauf
qu'à présent vos deux programmes doivent communiquer de manière bidirectionnelle, qu'on
appellera pair1 et pair2.

* Bien que la communication soit bidirectionnelle, pair1 et pair2 contiennent-ils exactement
  le même code ? Qu'est-ce qui les distingue et pourquoi ?

* Peux-t-on exécuter pair1 avant pair2 et inversement ? Si oui pourquoi, si non pourquoi ?

Comme pour la question 2 décrire précisement un cas où la communication entre pair1
et pair2 peux s'interbloquer.

Question 5:
===========

Un serveur exécuté sur la machine du prof en attente sur le port 9876 retransmet sur la sortie 
standard tout ce qui y est envoyé par des clients connectés. Le serveur utilise une socket
AF_INET/SOCK_STREAM. Ecrire un client qui se connecte au serveur, puis écrit sur la socket
tout ce qui est lu depuis l'entrée standard.

Question 6:
===========

Ecrire l'équivalent de la commande cat-server, mais fonctionnant sur un réseau TCP/IPv4. Un
programme client et un programme serveur doivent être écrit :

* Le programme cat-server lit tout ce qui provient d'une socket AF_INET de type de ligne 
  SOCK_STREAM et l'enverra sur la sortie standard. Il se mettre en attente sur un numéro
  de port indiqué en paramètre, sur toutes les adresses IP (INADDR_ANY) de la machine 
  sur laquelle cat-server est exécuté. 

  L'exemple suivant indique comment ées adresses sockets de type IPv4 sont renseignées avant
  d'effectuer l'appel à bind() :

      
      #include    <sys/types.h>
      #include    <sys/socket.h>
      #include    <netinet/in.h>
      #include    <arpa/inet.h>

      struct sockaddr_in catserv_addr;

      bzero((char *) &serv_addr, sizeof(serv_addr));
      serv_addr.sin_family        = AF_INET;
      serv_addr.sin_addr.s_addr   = htonl(INADDR_ANY); /* bind sur toutes les IPs de la machine */
      serv_addr.sin_port      = htons(1234);		  /* bind sur le port 1234 */

      if (bind(sockfd, (struct sockaddr *) &catserv_addr, sizeof(catserv_addr)) < 0)
        	perror("catserv: erreur bind");



* Après connexion à catserver, le programme cat-client lit tout ce qui vient de l'entrée standard et 
  l'écrira sur la socket connectée à catserver. En utilisant les redirection shell, utiliser vos
  deux programmes pour envoyer un fichier d'une machine à l'autre. Pour trouver l'adresse IP
  d'une machine et savoir où se connecter, utiliser la commande shell "ip addr show"

Est-ce que un catserver peux afficher le contenu des données provenant de plusieurs clients connectés ?
Expliquer pourquoi ? Modifier catserver pour qu'après chaque lecture sur la socket, il s'endorme une
seconde, le client écrira à la même vitesse. En utilisant les redirections shell sur cat-client, envoyer 
le code source de cat-server vers cat-server. Ce code source devrait être affiché sur la sortie
standard du terminal et de la machine d'exécution de cat-server.  Que constatez-vous ? 
Indiquer trois endroits où peuvent se trouver les données que le client a fini d'envoyer et que 
le serveur écrit toujours sur la sortie standard ?

Question 7:
===========

* Ecrire un serveur TCP/IP basé sur une socket AF_INET/SOCK_STREAM. Ce serveur s'attendra à recevoir
  la structure suivante depuis la socket, et l'affichera sur la sortie standard :


	struct data {
        	char name[7];
        	int id;
  	};

* Le client renseignera une structure identique avec les chants "toto" et 10 et l'enverra dans une socket 
  connectée au serveur.

Sur le client, modifier la déclaration de votre structure de la manière suivante :


	struct __attribute__ ((__packed__))" data {
        	char name[7];
        	int id;
  	};


Relancer votre client et renvoyer le contenu de la structure vers le serveur. Que constatez-vous et 
comment pouvez-vous l'expliquer ce résultat ? Pour l'expliquation se l'attribut "packed", se referrer
à l'url suivante : 

http://stackoverflow.com/questions/11770451/what-is-the-meaning-of-attribute-packed-aligned4

Question 8:
===========

En utilisant la fonction merveilleuse fonction getaddrinfo, écrire un serveur "echo" qui
fonctionne aussi bien en IPv6 qu'en IPv4, sur deux sockets distinctes. 

* Le serveur "echo" ne fait rien d'autre qu'écrire dans la socket d'un client connecté ce qu'il a recu. 

* A l'aide de fork(), modifier votre serveur pour qu'il puisse répondre à plusieurs clients "simultanément".
