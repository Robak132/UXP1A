#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>

int main()
{
    struct flock lock{}, savelock{};
    int fd;

    fd = open("file.txt", O_RDWR);
    lock.l_type = F_RDLCK;
    lock.l_start = 5;
    lock.l_whence = SEEK_SET;
    lock.l_len = 4;
    savelock = lock;
    if ((fcntl(fd,F_SETLKW,&savelock))==-1){
        perror("Error while locking file");
        exit(1);
    }
    printf("press enter to release lock\n");
    getchar();
    savelock.l_type = F_UNLCK;
    // savelock.l_whence = SEEK_SET;
    // savelock.l_start = 0;
    // savelock.l_len = 0;
    if((fcntl(fd,F_UNLCK,&savelock))==-1)
    {
            perror("fcntl");
            exit(0);
    }
    printf("Unlocked\n");
    close(fd);
}