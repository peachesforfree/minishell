



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
<<<<<<< HEAD
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
=======
   char     **oranges;

   oranges = make_str_ptr(argc);
>>>>>>> 09338966b4f29436927db52aceb9aa69177838d5

    return (0);
}

/*





*/