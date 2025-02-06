#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>


int main() {
    write(2,"message 1 avant dup(2)\n",23);
    int fd = open("MyErrors", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    int SauvStderr = dup(2);
    write(SauvStderr,"message 2 après dup(2)\n",23);
    dup2(fd,2);
    close(fd);
    write(2,"message 3 après dup2(fd,2)\n",28);    // maintenant on écrit dans le fichier MyErrors
    write(2,"message 4 après dup2(fd,2)\n",28);
    dup2(SauvStderr,2);
    write(2,"message 5 après dup2(SauvStderr,2)\n",36);
    return 0;
}



