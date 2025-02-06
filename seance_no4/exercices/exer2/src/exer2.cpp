/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include<unistd.h>
#include <fcntl.h>
int main() { 
   int fd = open("inf2610.txt", O_CREAT | O_WRONLY | O_TRUNC);
   dup2(fd,1);
   close(fd);
   execlp("ls", "ls", "-l", NULL);
   
    return 0;    
}