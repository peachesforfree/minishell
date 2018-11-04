



#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
//#include "libft/libft.h"

int     ft_strlen(char *str)
{
    int     i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

/*
    char **temp[1];
        \/
       0 [][][][][][][][]
       1 [][][][][][][][]
       2 [][][][][][][][]
       3 [N][U][L][L][L][][][]

*/

char    **make_str_ptr(int  count)
{
    char    **temp;

    temp = (char**)malloc(sizeof(char**) * count + 1);
    temp[count] = NULL;
    return (temp);
}

int main(int argc, char **argv)
{
   char     **oranges;

   oranges = make_str_ptr(argc);

    return (0);
}

/*





*/