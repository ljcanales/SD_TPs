
program MY_FS {
    version MY_FS_VER {
        string GET_FILE(string) = 1;
        int RELEASE_FILE(string) = 2;
        string GET_STATE() = 3;
    } = 1;
} = 0x20000001;