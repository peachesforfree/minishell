#include <stdio.h>
#include <unistd.h>


int main(int argc, char **argv, char **environ)
{
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tgetcwd(%s)\n", getcwd(NULL, 0));

    int ii = 0;
    while (environ[ii] != NULL)
        printf("%s\n", environ[ii++]);


    chdir(argv[1]);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tChanging curent working directory to: '%s'\n", argv[1]);
    printf("\t\t\t\t\t\t\t\t\t\t\t\t\tgetcwd(%s)\n", getcwd(NULL, 0));


    int i = 0;
    while (environ[i] != NULL)
        printf("%s\n", environ[i++]);
    return (0);
}