class Inode:
    def __init__(self, data):
        self.i_mode = data[0]
        self.i_uid = data[1]
        self.i_size = data[2]
        self.i_time = data[3]
        self.i_gid = data[4]
        self.i_nlinks = data[5]
        self.i_zone = data[6:12]
        self.i_indir_zone = data[13]
        self.i_dbl_indr_zone = data[14]
