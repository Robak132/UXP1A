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
    lock.l_start   = 8;
    lock.l_whence  = SEEK_SET;
    lock.l_len     = 7;
    savelock = lock;

    // fcntl(fd, F_GETLK, &lock);  /* Overwrites lock structure with preventors. */
    // if (lock.l_type == F_WRLCK)
    // {
    //     printf("Process %d has a write lock already!\n", lock.l_pid);
    //     printf("%ld, %ld\n", lock.l_start, lock.l_len);
    //     exit(1);
    // }
    // else if (lock.l_type == F_RDLCK)
    // {
    //     printf("Process %d has a read lock already!\n", lock.l_pid);
    //     printf("%ld, %ld\n", lock.l_start, lock.l_len);
    //     exit(1);
    // }
    // else
    // {
    //     fcntl(fd, F_SETLK, &savelock);
    //     // std::string s;
    //     // s = "ala ma kota";
    //     // std::string strBuff = "\n" + s;
    //     // const char *buf = strBuff.c_str();
    //     // lseek(fd, 0, SEEK_END);
    //     // write(fd, buf, strlen(buf));
    //     printf("File locked!\n");
    //     sleep(5);
    //     printf("5 seconds passed\n");
    //     savelock.l_type = F_UNLCK;
    //     fcntl(fd, F_SETLK, &savelock);
    //     printf("file unlocked\n");

    // }
    // close(fd);
    printf("trying to get lock..\n");
    int res = (fcntl(fd,F_SETLKW,&savelock));
    switch (res)
    {
    case EACCES:
        printf("EACCES\n");
        break;
    case EAGAIN:
        printf("EAGAIN\n");
        break;
    case EBADF:
        printf("EBADF\n");
        break;
    case EINTR:
        printf("EINTR\n");
        break;
    case EINVAL:
        printf("EINVAL\n");
        break;
    case EMFILE:
        printf("EMFILE\n");
        break;
    case ENOLCK:
        printf("ENOLCK\n");
        break;
    case EOVERFLOW:
        printf("EOVERFLOW\n");
        break;
    default:
        printf("%d\n", res);
        break;
    }
    if(res==-1)
    {     
        fcntl(fd,F_GETLK,&lock);
        printf("\nFile already locked by process (pid):    \t%d\n",lock.l_pid);
        printf("%d, %ld, %ld, %d\n", lock.l_type, lock.l_start, lock.l_len, lock.l_whence);   
        return -1;        
    }
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