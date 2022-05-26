#include <fstream>
#include <sys/sem.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

int main(){
    key_t semKey;
    int semId, readsemId;
    int fd; 
    char buff[255];
    char semx[10];
    int sid = syscall(SYS_gettid);
	semKey = ftok(".", sid);
	semId = semget( semKey, 1, IPC_CREAT | IPC_EXCL | 0660 );
    printf("%d, %d\n", semId, semKey);
    fd = open("sem.txt", O_RDWR);
    sprintf(semx, "%d", semId);
    write(fd, &semx, sizeof(semId));
    close(fd);
    struct sembuf sem_lock = { 0, -1, 0 };
    printf("sem waiting ...\n");
	int val = semop(semId, &sem_lock, 1);
    printf("semwait done\n");
    semctl(semId, 0, IPC_RMID);
    struct flock lock;
    char buffer[255];
    fd = open("file.txt", O_RDWR);
    lock.l_type    = F_RDLCK;   /* Test for any lock on any part of file. */
    lock.l_start   = 0;
    lock.l_whence  = SEEK_END;
    lock.l_len     = -5;
    printf("trying to get lock..\n");
    if ((fcntl(fd,F_SETLKW,&lock))==-1){
        perror("Error while locking file");
        exit(1);
    }
    printf("locked\n");
    if((lseek(fd,-4,SEEK_END))==-1)
    {
            perror("lseek");
            exit(1);
    }
    if((read(fd,buffer,4))==-1)
    {
            perror("write");
            exit(1);
    }

    printf("data read from file..\n");
    if(strcmp(buffer, "abc"))
    {
        puts(buffer);
    }
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

    return 0;
}