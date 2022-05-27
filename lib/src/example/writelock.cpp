#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

int main() {
    int fd;
    struct flock lock{}, savelock{};
    std::string line = "1,-15.5,Słoń,42,,,";
    const char *buf = line.c_str();

    fd = open("file.txt", O_RDWR);
    lock.l_type    = F_WRLCK;   /* Test for any lock on any part of file. */
    lock.l_start   = 0;
    lock.l_whence  = SEEK_END;
    lock.l_len     = sizeof(line);
    savelock = lock;
    
    printf("trying to get lock..\n");
    int res = (fcntl(fd,F_SETLKW,&savelock));
    if(res==-1)
    {     
        fcntl(fd,F_GETLK,&lock);
        printf("\nFile already locked by process (pid):    \t%d\n",lock.l_pid);
        printf("%d, %ld, %ld, %d\n", lock.l_type, lock.l_start, lock.l_len, lock.l_whence);   
        return -1;        
    }
    printf("locked\n");
    if((lseek(fd,0,SEEK_END))==-1)
    {
            perror("lseek");
            exit(1);
    }
    if((write(fd, buf, sizeof(line)))==-1)
    {
            perror("write");
            exit(1);
    }
    printf("press enter to release lock\n");
    getchar();
    savelock.l_type = F_UNLCK;
    savelock.l_whence = SEEK_SET;
    savelock.l_start = 0;
    savelock.l_len = 0;
    if((fcntl(fd,F_UNLCK,&savelock))==-1)
    {
            perror("fcntl");
            exit(0);
    }
    printf("Unlocked\n");
    close(fd);
    return 0;
}