



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"
#include <sys/types.h>



int main(int argc, char **argv, char **environ)
{
    char *input;
    char    *ret;
    int     chr;

    input = NULL;
    ret = NULL;
    chr = 0;
    
    ret = getcwd(NULL, 0);
    while (get_next_line(1, &input))
    {

        chr = chdir(input);
        if (chr == 0)
            printf("success\t %s/%s \t is a proper directory\n", ret, input );
        else
            printf("Sorry %s/%s is not a proper directory\n", ret, input);
    }

    return (0);
}