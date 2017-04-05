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


def getInode(id):
    file.seek(firstInodeTableBlk * blkSize)
    data = struct.unpack("<HHIIBBHHHHHHHHH", file.read(iNodeSize))
    return Inode(data)


node = getInode(1)
print node

# this is false
file.seek(firstBitmapBlk * blkSize)
temp = struct.unpack("<HBBBBBBBBBBBBBB", file.read(16))
print temp

file.close()
