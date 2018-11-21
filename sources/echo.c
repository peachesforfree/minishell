#include <../includes/mini_shell.h>

int     ft_echo(t_env *env, char **argv_ptr)
{
    int     ret;
    int     i;

    i = 1;
    (void)env;
    ret = 0;
    if (argv_ptr[i] != NULL)
    {
        while (argv_ptr[i] != NULL)
        {
            printf("%s", argv_ptr[i]);
            if (argv_ptr[i + 1] != NULL)
                printf(" ");
            i++;
        }
        printf("\n");
    }
    return (ret);
}