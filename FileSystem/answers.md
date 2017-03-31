I. Questions sur la structure du super-bloc, et des structures d'allocations de blocs/inodes
--------------------------------------------------------------------------------------------

1. Quel est le nombre de blocs du volume ?
    20480, on peut voir ça à l'octet 3-4 du bloc 1
2. Quel est le nombre maximum d'inodes que l'on peut créer ?
    6848, bit 0 du bloc 1 (sur 2 octets)

3. Quel(s) sont le/les numéros de bloc qui contient/nent le bitmap des blocs disponibles ?
* Numéros : 3 à 5

Explications :

- à l'offset 6 du bloc 1, le superbloc indique 3 blocs utilisés pour contenir
  la bitmap des blocs disponibles.
- On ne peut pas encore répondre car il faut savoir
  combien de blocs sont utilisés par le bitmap des inodes disponibles. (octet 4-5 du bloc 1)
- Après résolution de la question 4, et comme les blocs de bitmap de blocs disponibles sont
  situés juste aprés les blocs d'inodes disponibles.


4. Quel(s) sont le/les numéros de blocs qui contient/nent le bitmap des inodes disponibles ?

* Numéros : 2

Explications :

- à l'offset 4 du bloc 1 le superbloc indique 1 bloc utilisé, situé juste après le superbloc.

5. Quel(s) sont le/les numéros de blocs qui contiennent la table des inodes ?
1 inode = 256 bits = 32 octets (calculé à partir de la struct)
question 2, on a 6848 inodes, du coup 6848 * 32 = 219136 octets, blocs de 1024 octets donc 219136 / 1024 = 214 blocs

Donc, le premier bloc libre est le 6, jusqu'à 219 (et on sait que la first data zone est à 220)

6. Combien y-a-t-il d'inodes par bloc ?
bloc = 1024 octets, inode = 32 octets, du coup 1024 / 32 = 32 inodes/bloc

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