#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
int main()
{   int fd[2], i=2;
    char ch[100];
    while (i)
      { pipe(fd);
        if( fork())
            { close(fd[0]);
              dup2(fd[1],1);
              close(fd[1]);
              break;
            } else
            { close(fd[1]);
              dup2(fd[0],0);
              close(fd[0]);
            }
        i--;
      }
    scanf("%s", ch);
    printf("%s\n",ch);
    _exit(0);
}
