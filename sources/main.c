#include "../includes/mini_shell.h"

int         event_loop(t_env *env)
{
    int     ret;

    ret = 0;
    while (ret == 0 && read_line(env))
    {
        if (parse_command_line(env) < 0)
            printf("Error message\n");//make some error message
        ret = execute_command(env);
    }
    return (0);
}   //if return -1. something wrong ... if return >= 0 all is good

int         main(int argc, char **argv, char **environ)
{
    t_env   env;
    (void)argc;
    (void)argv;

    env_init(&env, environ);
    if (event_loop(&env) < 0)
    {
        //deconstruct();
        return (-1);
    }
    //deconstruct()
    return (0);
}


/****************
 *                      gcc take3.c -g includes/mini_shell.h libft/libft.a
 *              fix the ENV espansion (only chooses the first item in the list)     Read notes command+parse.c Line 51
 *              free everything
 *              Make file ... check other make files how to pre or post pend ... need to prepend the sources directory
 * **********************/