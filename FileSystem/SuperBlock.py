class SuperBlock:
    def __init__(self, data):
        self.inodesCount = data[0]
        self.blkCount = data[1]
        self.imapBlks = data[2]
        self.zmapBlks = data[3]
        self.firstData = data[4]
        self.dataBlkSize = data[5]
        self.maxFileSize = data[6]
        self.magic = data[7]
        self.state = data[8]
