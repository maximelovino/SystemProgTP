Question 1:
===========

Ecrire la fonction C void block_unblock(int fd). Cette fonction
aura le comportement d'un interrupteur sur la valeur du flag
O_NONBLOCK d'un descripteur de fichier donné en paramètre : si
le flag est posé, elle le met à zéro, si le flag n'est pas
posé, elle le pose. Votre fonction devra vérifier que l'appel
à fcntl a bien réussi, sinon elle affichera une erreur sur
l'erreur standard avec perror().

Question 2:
===========

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


Question 3:
===========

Modifier le programme de la question 2 pour que les fils utilisent aussi select(). 
Placer dans ce cas l'attente dans l'appel système select().

Question 4:
===========

En utilisant la fonction merveilleuse fonction getaddrinfo, écrire un serveur "echo" qui
fonctionne aussi bien en IPv6 qu'en IPv4, sur deux sockets distinctes. 

* Le serveur "echo" ne fait rien d'autre qu'écrire dans la socket d'un client connecté ce qu'il a recu. 

* A l'aide de select(), modifier votre serveur pour qu'il puisse répondre à plusieurs clients "simultanément
  bien qu'il soit mono-processus.

* A l'aide de select(), modifier votre serveur pour qu'il puisse répondre à plusieurs clients "simultanément
   bien qu'il soit mono-processus.

Question 5:
===========

Créer un anneau de communication entre 3 processus p1,p2,p3 relié l'un à l'autre 
par les pipes, pi1, pi2, pi3. Chacun des processus commençent par l'écriture. p1 écrit
puis lit continuellement et respectivement dans pi2 et pi1. p2 écrit puis lit continuellement
et respectivement dans pi3 et pi2. p3 écrit puis lit continuellement et respectivement dans
pi1 et pi3. Modifier les longueurs des buffers écrites de telle sortes à ce qu'il y ait interblocage.

Modifier votre programme en utilisant la fonction de la question 1 pour qu'il n'y ait
plus de blocage. Observer l'utilisation CPU du programme modifié avec htop.

Question 6:
===========

Ecrire en C et avec les sockets un serveur HTTP mono-processus minimaliste basé sur select(). 
Le serveur se mettra en attente d'une nouvelle connexion TCP sur le port choisi en
ligne de commande. Une fois la connexion acceptée, le serveur affiche localement l'adresse
complète du navigateur qui s'est connecté (adresse IPv4/IPv6 et numéro de de port), lit la requête du
navigateur et affiche son contenu.

N'importe quel client HTTP vous permettra de tester votre programme et de découvrir la syntaxe
des requêtes du protocole HTTP. Il est en effet possible de préciser le numéro de port dans l'adresse du
navigateur. Un client http permettant de rapidement tester le comportement de votre programme en
ligne de commande est wget(1). Pour vous connecter en IPv6 avec wget, utilisez l'option -6.
Par exemple : l'adresse http://A433-01:12345/bonjour.txt précise que le fichier bonjour.txt se
trouve sur la machine A433-01 accessible en http sur le numéro de port 12345.

Une requête de la part du client HTTP de la forme GET <chemin_acces> HTTP/1.1 sera
interprétée par votre serveur comme une demande de téléchargement du fichier se trouvant à la
position chemin_acces par rapport au répertoire où est lancé le serveur. Elle générera une
réponse de la forme :


	HTTP1/1 200 OK
	Content-length : nnn
	<contenu du fichier>

Qui précise la taille nnn et le contenu du fichier. Si le fichier n'est pas accessible, votre serveur
devra renvoyer une réponse de la forme


	HTTP/1.1 404 Not found
	Content-type: text/html
	<html><head><title>Not Found</title></head><body>
	Sorry, file not found.
	</body><html>


Question 7:
===========

A. Description générale :
-------------------------

Le but de l'exercice suivant est d'écrire un mini-serveur de blocs en C issus d'un seul fichier
donné en paramètre. Les blocs d'un fichier, adressé par leur offset et leur longueur dans le
fichier, pourront être écrits ou lus à distance par un seul client (i.e pas d'accès concurrent possible), 
les ordres d'écritures ou de lecture apparaissant dans les données transportée par le réseau.

Pour cela Le serveur  devra implémenter un simple protocole requête-réponse qui 
respecte le format de messages suivant, transporté sur TCP/IP via des sockets 
C AF_INET de type SOCK_STREAM. 

Le serveur sera exécuté en ligne de commande avec la syntaxe suivante. Il
tournera continuellement en attente de messages de la part du client.

hoerdtm@A406-01:~$ ./bloc_server <nom_du_fichier_a_servir>


B. Format des requêtes :
------------------------


             0                1               2                3 
        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       |        Magic header separator Signature=0x76767676            | 
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       |                          Type                                 |          
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       +                          Handle                               + 
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       |                          Offset                               |          
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       |                          Length                               |          
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       .                          Payload                              . 
       .             Présent seulement si type=CMD_WRITE               . 
       .                                                               . 



Format des réponses :


             0                1               2                3 
        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       |           Magic header separator Signature=0x87878787         | 
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       |                          Error                                |          
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       |                          Handle                               |          
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ 
       .                          Payload                              . 
       .           Présent seulement si réponse à CMD_READ             . 
       .                                                               . 
        
        

Les paragraphes qui suivent décrivent les différents champs du protocole :

* Magic header separator Signature : Simplement un nombre bien connu sur 32 bits qui permet d'éviter 
  le traitement de message qui ne commenceraient pas par cette signature protocolaire. C'est un indicateur
  de début de message puisque ceux-ci arrivent dans un flux d'octets dont on ne peut prévoir la
  vitesse d'arrivée. En clair : un read(), ne renverra pas forcément le nombre d'octets attendu et
  il faut avoir un buffer intermédiaire. Une requête commence par le numéro magique 0x76767676, 
  une réponse commence par le numéro magique 0x87878787

* Type : un entier sur 32 bits qui définit le type de la requête. Deux valeurs possibles :
         
         0x0 = CMD_READ
         0x1 = CMD_WRITE 
 
* Error : Uniquement dans les messages de type réponse. Il indique le résultat d'une commande 
  qu'un client à demander à effectuer, une valeur à zéro indique que la commande a été effectuée
  avec succès, une valeur négative indique une erreur, qui corresponds à la valeur qu'on trouverait
  dans errno si la requête était effectuée localement.

* Handle : 32 bits qui identifient de manière unique une requête et qui permet 
  aux clients d'identifier une reponse à une requête et donc de demander plusieurs requêtes en même 
  temps avant de traiter leur réponse : c'est du pipelining.
  Dans une réponse, le champs Error indique le retour d'erreur/non erreur pour une requête dont le numéro
  de handle était identique à celui indiqué dans la réponse. L'initialisation du Handle pour une requête
  devra utiliser la fonction rand(3) de la librairie C associée à une seed initialisée à sur la valeur
  de l'heure locale du système du client.

* Offset : un entier sur 32 bits qui indique à partir de quel offset en octet doit
  commencer la requête d'écriture ou de lecture.

* Length : longueur des octets à lire ou à écrire qui suivent l'entête du protocole.

* Payload : Les données lues dans une réponse à une requête de lecture, les données à
  écrire dans une requête d'écriture. Dans une réponse à une requête d'écriture, le payload
  est vide, le message contenant uniquement un code d'erreur et le handle correspondant. 


C. Petits détails qui tuent
---------------------------

Le format des requêtes devra être codée avec une structure C. Pour s'assurer
que leur sérialisation prenne bien le nombre d'octets spécifié, les déclarer
de la manière suivante :


     struct __attribute__ ((__packed__))" <nom_de_la_structure> {

     }

L'ensemble des données devront être représentées en big endian, c'est à dire l'ordre 
conventionnel pour l'ensemble des protocole réseaux TCP/IP : les bits de poids fort 
sont en premier : utiliser les primitives htonl et ntohl.

Pour simplifier, le serveur sera conçu pour servir une seule requête à la fois et 
un seul client à la fois, identifiée par le champs Handle des messages. Il n'est donc 
pas nécessaire d'écrire un serveur multi-processus ni d'utiliser les mécanismes 
tels que select() ou les descripteurs de fichiers non bloquants.

*Important* : Comme les sockets de type SOCK_STREAM sont utilisées pour transmettre 
un flux de données qui est agnostique au type de données transporté, elles ne préservent 
pas la séparation entre les différents structures qui composent la communication.  Ceci
veut dire que sur un flux composé d'une requête d'écriture longue de N octets 
telle que illustrée sur la figure suivante :

     -------------------->
     |N|...|6|5|4|3|2|1|0| 
     -------------------->

Un premier appel à read(s,buffer,10) sur la socket, peut renvoyer un nombre d'octet dans
le buffer compris entre 0 et 10. Si on veut récupérer les N octets, il faudra s'assurer
que la somme des octets reçus successivement dans le flux composent bien une requête en 
entier.

D. Exemple de communication :
-----------------------------

1. Client envoie au serveur : 0x76767676, 0x0, 0x12345678, 0x1000, 0x400

=> c'est une requête (0x76767676) de lecture (0x0), de handle 0x12345678, à l'offset 0x1000 du fichier, de 1024 (0x400) octets.

2. Le serveur se positionne à l'offset 1024 du fichier passé en paramètre (cf lseek(2)), lit 1024 octets (cf read(2)) dans
   un buffer, puis renvoit la réponse suivante :

   0x87878787,0x0, 0x12345678, données lues (1024 octets).

=> c'est une réponse (0x87878787), sans erreur (0x0), pour la requêtel 0x12345678, qui contient 1024 octets
