import re

filename = 'TP3_minixfs_lab1_dump_blocs.txt'

file = open(filename)

superblock = False


for line in file:
    if re.search('(=)+Bloc 1(=)+','')

file.close()
