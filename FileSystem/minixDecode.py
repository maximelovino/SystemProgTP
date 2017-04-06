# -*- coding: utf-8 -*-

import struct
from SuperBlock import *
from Inode import *

filename = 'minixfs_lab1.img'
blkSize = 1024
superBlockId = 1
file = open(filename)

iNodeSize = 32

print "I. Questions sur la structure du super-bloc, et des structures d'allocations de blocs/inodes"

# skip block 0
file.seek(blkSize * superBlockId)
# Read superblock
# TODO check to do in a superblock object
data = struct.unpack("<HHHHHHIHH", file.read(20))

superBlock = SuperBlock(data)

print "1. Quel est le nombre de blocs du volume ?"
print superBlock.blkCount
print "==============="
print "2. Quel est le nombre maximum d'inodes que l'on peut créer ?"
print superBlock.inodesCount
print "==============="
print "3. Quel(s) sont le/les numéros de bloc qui contient/nent le bitmap des blocs disponibles ?"
firstBitmapBlk = superBlockId + superBlock.imapBlks + 1
lastBitmapBlk = firstBitmapBlk + superBlock.zmapBlks - 1
print  "Du bloc " + str(firstBitmapBlk) + " jusqu'au bloc " + str(lastBitmapBlk)
print "==============="
print "4. Quel(s) sont le/les numéros de blocs qui contient/nent le bitmap des inodes disponibles ?"
firstImapBlk = superBlockId + 1
lastImapBlk = firstImapBlk + superBlock.imapBlks - 1
print str(firstImapBlk) + " jusqu'au " + str(lastImapBlk)
print "==============="

print "5. Quel(s) sont le/les numéros de blocs qui contiennent la table des inodes ?"
inodeTableBlks = (iNodeSize * superBlock.inodesCount) / blkSize
firstInodeTableBlk = lastBitmapBlk + 1
lastInodeTableBlk = firstInodeTableBlk + inodeTableBlks - 1
print str(firstInodeTableBlk) + " jusqu'au " + str(lastInodeTableBlk)
print "==============="
print "6. Combien y-a-t-il d'inodes par bloc ?"
print blkSize / iNodeSize
print "==============="

print 'II. Questions de navigation dans le système de fichier'
print 'Le but des questions suivantes est d\'examiner le contenu du fichier /usr/src/archives/linux-0.95.tgz et en particulier le contenu des octets d\'adresses 600000 à 600009 du fichier.'
print "==============="
print "==============="


def findInNode(nodeId, search):
    rootNode = getInode(nodeId)
    file.seek(blkSize * rootNode.i_zone[0])
    while True:
        id = struct.unpack("<H", file.read(2))
        name = struct.unpack("<BBBBBBBBBBBBBB", file.read(14))
        letters = [chr(i) for i in name if i != 0]
        letters = ''.join(letters)
        if letters == search:
            return (id[0], letters)


def getInode(id):
    file.seek(firstInodeTableBlk * blkSize + (id - 1) * iNodeSize)
    data = struct.unpack("<HHIIBBHHHHHHHHH", file.read(iNodeSize))
    return Inode(data)


def getInodeIDOfFile(nameOfFile):
    path = nameOfFile.split('/')
    currentNode = 1
    for i in path:
        if i != '':
            currentNode = findInNode(currentNode, i)[0]

    return currentNode


def getInodeOfFile(name):
    return getInode(getInodeIDOfFile(name))


fileNode = getInodeOfFile('/usr/src/archives/linux-0.95.tgz')
print fileNode.i_size

print '1. Quel sont le ou les numéros de blocs contenant les entrées du répertoire / ainsi que la taille de répertoire ? Rappel : inode 1 = la racine.'
tempNode = getInode(1)
print "Les numéros de blocs sont : " + str(tempNode.i_zone)
print "La taille est : " + str(tempNode.i_size)
print "==============="
print '2. Quel est le numéro d\'inode du répertoire /usr ?'
tempID = getInodeIDOfFile('/usr')
print "Le numéro d'iNode est " + str(tempID)
print "==============="
print '3. Quels sont le ou les numéros des blocs contenant les entrées du répertoire /usr ainsi que la taille de ce répertoire ?'
tempNode = getInode(tempID)
print "Les numéros de blocs sont : " + str(tempNode.i_zone)
print "La taille est : " + str(tempNode.i_size)
print "==============="
print '4. Quel est le numéro d\'inode du répertoire /usr/src ?'
tempID = getInodeIDOfFile('/usr/src')
print "Le numéro d'iNode est " + str(tempID)
print "==============="
print '5. Quels sont le ou les numéros des blocs contenant les entrées du répertoire /usr/src ainsi que la taille de ce répertoire ?'
tempNode = getInode(tempID)
print "Les numéros de blocs sont : " + str(tempNode.i_zone)
print "La taille est : " + str(tempNode.i_size)
print "==============="
print '6. Quel est le numéro d\'inode du répertoire /usr/src/archives ?'
tempID = getInodeIDOfFile('/usr/src/archives')
print "Le numéro d'iNode est " + str(tempID)
print "==============="
print '7. Quels sont le ou les numéros des blocs contenant les entrées du répertoire /usr/src/archives ainsi que la taille de ce répertoire ?'
tempNode = getInode(tempID)
print "Les numéros de blocs sont : " + str(tempNode.i_zone)
print "La taille est : " + str(tempNode.i_size)
print "==============="
print '8. Quel est le numéro d\'inode du fichier /usr/src/archives/linux-0.95.tgz?'
tempID = getInodeIDOfFile('/usr/src/archives/linux-0.95.tgz')
print "Le numéro d'iNode est " + str(tempID)
print "==============="
print '9. Quelle est la taille de ce fichier ?'
tempNode = getInode(tempID)
print "La taille est : " + str(tempNode.i_size)
print "==============="
print '10. Quelle est le nombre total de blocs occupés par ce fichier ? Combien d\'octets contient le dernier bloc du fichier ?'
print tempNode.i_zone
print tempNode.i_indir_zone
print tempNode.i_dbl_indr_zone
if tempNode.i_size % blkSize != 0:
    print "Le nombre de blocs sera de : " + str(tempNode.i_size / blkSize + 1)
    print "Dans le dernier bloc il y aura : " + str(tempNode.i_size % blkSize) + " octets"
else:
    print "Le nombre de blocs sera de : " + str(tempNode.i_size / blkSize)
    print "Dans le dernier bloc il y aura : " + str(blkSize) + " octets"
print "==============="
file.close()
