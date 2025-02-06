#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char* argv[]) {
    if(argc!=2) _exit(1);
    int fd[2];
    char buf;
    pipe(fd);
    if (fork() == 0) { // le fils est un lecteur
        close(fd[1]);
        while (read(fd[0], &buf, 1) > 0) { write(1, &buf, 1); }
        write(1, "\n", 1);
    close(fd[0]);
    } else { // le père est un écrivain
        close(fd[0]);
        write(fd[1], argv[1], strlen(argv[1])+1);
        close(fd[1]);
        wait(NULL); // attend la fin de son fils
    }
_exit(0);
}