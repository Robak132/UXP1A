#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/sem.h>

int main(){
    int fd;
    char buff[255];
    int semId;
    fd = open("sem.txt", O_RDONLY);
    read(fd, buff, sizeof(int));
    semId = strtol(buff, NULL, 10);
    printf("%d\n", semId);
    close(fd);
    struct flock lock;
    fd = open("file.txt", O_RDWR);
    lock.l_type    = F_WRLCK;   /* Test for any lock on any part of file. */
    lock.l_start   = 0;
    lock.l_whence  = SEEK_END;
    lock.l_len     = 5;
    printf("trying to get lock..\n");
    if ((fcntl(fd,F_SETLKW,&lock))==-1){
        perror("Error while locking file");
        exit(1);
    }
    printf("locked\n");
    if((lseek(fd,0,SEEK_END))==-1)
    {
            perror("lseek");
            exit(1);
    }
    if((write(fd,"\nabc",4))==-1)
    {
            perror("write");
            exit(1);
    }
    struct sembuf sem_unlock = { 0, 1, 0 };
	int val = semop(semId, &sem_unlock, 1);
    printf("press enter to release lock\n");
    getchar();
    lock.l_type = F_UNLCK;
    if((fcntl(fd,F_UNLCK,&lock))==-1)
    {
            perror("fcntl");
            exit(0);
    }
    printf("Unlocked\n");
    close(fd);

}