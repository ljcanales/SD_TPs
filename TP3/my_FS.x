
program MY_FS {
    version MY_FS_VER {
        string GET_FILE(string) = 1;
        int REALEASE(string) = 2;
    } = 1;
} = 0x20000001;