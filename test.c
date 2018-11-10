#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int     main(int argc, char **argv, char **environ)
{
    if (execve("/bin/ls", argv, environ) < 0)
        printf("ERRNO MSG: %s\n", strerror(errno));
    return (0);
}