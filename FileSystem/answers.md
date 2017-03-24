I. Questions sur la structure du super-bloc, et des structures d'allocations de blocs/inodes
--------------------------------------------------------------------------------------------

1. Quel est le nombre de blocs du volume ?
    20480, on peut voir ça au bit 16 du bloc 1
2. Quel est le nombre maximum d'inodes que l'on peut créer ?
    6848, bit 0 du bloc 1

3. Quel(s) sont le/les numéros de bloc qui contient/nent le bitmap des blocs disponibles ?
* Numéros : 3 à 5

Explications :

- à l'offset 6 du bloc 1, le superbloc indique 3 blocs utilisés pour contenir
  la bitmap des blocs disponibles.
- On ne peut pas encore répondre car il faut savoir
  combien de blocs sont utilisés par le bitmap des inodes disponibles.
- Après résolution de la question 4, et comme les blocs de bitmap de blocs disponibles sont
  situés juste aprés les blocs d'inodes disponibles.


4. Quel(s) sont le/les numéros de blocs qui contient/nent le bitmap des inodes disponibles ?

* Numéros : 2

Explications :

- à l'offset 4 du bloc 1 le superbloc indique 1 bloc utilisé, situé juste après le superbloc.

5. Quel(s) sont le/les numéros de blocs qui contiennent la table des inodes ?
1 inode = 256 bits = 32 octets
question 2, on a 6048 inodes, du coup 6848 * 32 = 219136, blocs de 1024 donc 219136 / 1024 = 214

Donc, le premier bloc libre est le 6, jusqu'à 219

6. Combien y-a-t-il d'inodes par bloc ?
bloc = 1024, inode = 32, du coup 1024 / 32 = 32 inodes/bloc