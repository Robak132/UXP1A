#include "../include/FileManager.h"

int main(){
    struct flock lock;
    lock.l_type    = F_WRLCK;
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 0;
    FileManager file("test.txt");
    file.lockFile(lock);
    printf("press enter to release lock\n");
    getchar();
    file.unlockFile();
    file.closeFile();
}