A. Rappels des structures de données de Minix fs 1.0
====================================================

En C, la structure du superbloc, d'un inode et d'une entrée de répertoire MINIX 
sont les suivantes :


	struct minix_super_block {
    		u16 s_ninodes;          /* Total Number of i-nodes */
    		u16 s_nzones;           /* Nombre de blocs total, tout compris, y compris bloc 0 */
    		u16 s_imap_blocks;      /* Taille de la bitmap des inodes en blocs (I bitmap) */
    		u16 s_zmap_blocks;      /* Taille de la bitmap des zones libres/occupée en blocs (D bitmap)*/
    		u16 s_firstdatazone;    /* Index du premier bloc avec des données (D) */
    		u16 s_log_zone_size;    /* taille d'un bloc données en octets = 1024*2s_log_zone_size */
    		u32 long s_max_size;    /* Taille maximum d'un fichier en octets */
    		u16 s_magic;            /* 0x137f Minix filesystem version 1, si on lit 7f13, on est sur architecture big endian*/
    		u16 s_state;            /* as-t-il été proprement démonté ? */
	};


	struct minix_inode {
    		u16 i_mode;             /* File type and permissions for file */
    		u16 i_uid;              /* user id */
    		u32 i_size;             /* File size in bytes */
    		u32 i_time;             /* inode time */
    		u8  i_gid;              /* group id */
    		u8  i_nlinks;           /* number of path pointing to this inode */
    		u16 i_zone[7];          /* Adresse logique des blocs direct du fichier */
    		u16 i_indir_zone;       /* adresse logique d'un bloc contenant des n° de blocs du fichier */
    		u16 i_dbl_indr_zone;    /* adresse logique d'un bloc contenant des n° de blocs qui contiennent des n° de blocs */
	};


	#define MINIX_NAME_LEN 14
		struct minix_dir_entry {
    		u16 inode;                  /* numéro d'inode */
    		char name[MINIX_NAME_LEN];  /* nom du fichier, 14 octets maximum, encodage des caractères libre (ascii, utf-8, ...)*/
	};

u16 indique implicitement la taille du champs de la structure = unsigned int sur 16 bits = 2 octets. 
un type u32 a une taille de 4 octets. Un tableau de n * u16 éléments aura une taille 
de n * 2 octets.

B. But et moyens du laboratoire
===============================

Le but des questions suivantes est de se familiariser avec 
les traitements effectués sur les structures de données 
disque du système de fichier Minix. 

L'image du volume contenant le système de fichier minix utilisé
pour répondre aux questions se trouve sur : 

https://hepia.infolibre.ch/syst-exploitation-2016-2017/minixfs_lab1.img.gz

Elle est compressée au format gzip, il faut la décompresser si vous voulez
en lire le contenu binaire. Afin de vous faciliter la résolution des questions, 
un dump hexadécimal ASCII d'une partie des blocs de ce volume est disponible sur :

https://hepia.infolibre.ch/syst-exploitation-2016-2017/TP3_minixfs_lab1_dump_blocs.txt

Ce dump, sur troix colonnes, indique avant chaque bloc du volume son numéro par l'entête suivante

                        ======Bloc n======

* La première colonne à gauche indique l'offset dans le bloc en décimal
* La colonne du milieu indique le contenu des 16 octets qui suivent 
  l'offset indiqué, le premier octet de la suite étant à l'adresse indiqué 
  à sa gauche. Sur la première ligne de chaque offset, les 16 octets sont 
  groupés par paquets de 2 et leurs valeurs hexadécimales décodée en *little endian* est
  affichée. Sur la deuxième ligne, la valeur correspondante décimale est affichée.
* La dernière colonne indique les caractères ascii imprimables dans chaque suite
  de 16 octets, un caractère non imprimable est indiqué par un '.', à ne pas confondre
  avec la valeur hexadécimale du caractère ascii "." qui vaut 0x2E.

Example pour le bloc 4346 :


                   ======Bloc 4346======
     00000 3029  1EA6  4049  33F1  5268  FC88  75FD  5421   )0..I@.3hR...u!T
           12329 07846 16457 13297 21096 64648 30205 21537  
     00016 55FA  35D2  089E  532C  278E  F359  4A80  43CB   .U.5..,S.'Y..J.C
           22010 13778 02206 21292 10126 62297 19072 17355  
     00032 8FAC  631A  C006  B029  A807  269B  74C0  C780   ...c..)....&.t..
           36780 25370 49158 45097 43015 09883 29888 51072  
     00048 425B  0D8F  3903  45A7  8CB4  C0C4  19CA  CCB6   [B...9.E........

le début du bloc contient les octets dans l'ordre 0x29 0x30 0xA6 0x1E 0x49 0x40. 
Ces octets sont indiqués à l'offset 0 du bloc, décodés par paquets de 2 octets
en little endian comme les valeurs hexadécimales 0x3029 0x1E46 0x4049, qui
correspondent aux valeurs décimales 12329, 7846 et 16457. L'octet 0xA6 est
à l'offset 3 du bloc 4346.

C. Questions
============

Veuillez répondre aux questions suivantes, dans l'ordre :

I. Questions sur la structure du super-bloc, et des structures d'allocations de blocs/inodes
--------------------------------------------------------------------------------------------

1. Quel est le nombre de blocs du volume ?
2. Quel est le nombre maximum d'inodes que l'on peut créer ?
3. Quel(s) sont le/les numéros de bloc qui contient/nent le bitmap des blocs disponibles ?
4. Quel(s) sont le/les numéros de blocs qui contient/nent le bitmap des inodes disponibles ?
5. Quel(s) sont le/les numéros de blocs qui contiennent la table des inodes ? 
6. Combien y-a-t-il d'inodes par bloc ?

II. Questions de navigation dans le système de fichier
------------------------------------------------------

Le but des questions suivantes est d'examiner le contenu du fichier /usr/src/archives/linux-0.95.tgz et 
en particulier le contenu des octets d'adresses 600000 à 600009 du fichier.

1. Quel sont le ou les numéros de blocs contenant les entrées du répertoire / ainsi que la taille de répertoire ? 
   Rappel : inode 1 = la racine.
2. Quel est le numéro d'inode du répertoire /usr ?
3. Quels sont le ou les numéros des blocs contenant les entrées du répertoire /usr ainsi que la taille de ce répertoire ?
4. Quel est le numéro d'inode du répertoire /usr/src?
5. Quels sont le ou les numéros des blocs contenant les entrées du répertoire /usr/src ainsi que la taille de ce répertoire?
6. Quel est le numéro d'inode du répertoire /usr/src/archives ?
7. Quels sont le ou les numéros de blocs contenant les entrées du répertoire /usr/src/archives ainsi que la taille de ce répertoire?
8. Quel est le numéro d'inode du fichier /usr/src/archives/linux-0.95.tgz?
9. Quelle est la taille de ce fichier ?
10. Quelle est le nombre total de blocs occupés par ce fichier ? Combien d'octets contient le dernier bloc du fichier ?
11. Quels sont le ou les numéros de ces blocs ?
12. Quel est le contenu des octets 600000 à 600009 du fichier ?

III. Type de fichiers particuliers
----------------------------------

1. En traversant la hiérarchie de répertoire depuis la racine, déterminer la taille et 
   le type du fichier /root/linux ?
2. Quel est le contenu et la taille de ce fichier ?

IV. La question challenge
-------------------------

Concevoir un programme dans le langage de votre choix pour extraire entièrement 
de l'image https://hepia.infolibre.ch/syst-exploitation-2016-2017/minixfs_lab1.img.gz
tous les blocs du fichier /usr/src/archives/linux-0.95.tgz. Concaténer le contenu des 
blocs extraits comme il faut et vérifier que votre extraction a bien fonctionné 
en essayant de décompresser l'archive.
