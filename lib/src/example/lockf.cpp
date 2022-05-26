#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

int main() {
    int fd;
    struct flock lock{}, savelock{};
    char buffer[255];

    fd = open("file.txt", O_RDWR);
    lock.l_type    = F_WRLCK;   /* Test for any lock on any part of file. */
    lock.l_start   = 0;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 7;
    savelock = lock;

    lockf(fd, F_LOCK, 0);
    printf("locked\n");
    if((lseek(fd,0,SEEK_SET))==-1)
    {
            perror("lseek");
            exit(1);
    }
    if((read(fd,buffer,4))==-1)
    {
            perror("read");
            exit(1);
    }
    printf("data read from file..\n");
    puts(buffer);
    printf("press enter to release lock\n");
    getchar();
    if((lockf(fd,F_ULOCK,0))==-1)
    {
            perror("lockf");
            exit(0);
    }
    printf("Unlocked\n");
    close(fd);
    return 0;
}