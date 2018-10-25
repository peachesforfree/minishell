



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"




int main(int argc, char **argv, char **environ)
{
    int i;
    char **ret;

    i = 0;
    ret = parse(argv[1]);

//    while (ret[i] != NULL)
//    {
//        printf("%s\n", ret[i]);
//        i++;
//    }

    return (0);
}