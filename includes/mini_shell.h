#ifndef MINI_SHELL_H
# define MINI_SHELL_H

#include <stdio.h>
#include <fcntl.h> //open write close
#include <../libft/linft.h>

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#define STDIN           0
#define EXECLOC         "PATH"
#define STDIN_BUFFER    4096
#define COMMAND_PROMPT  "$>"
#define EXIT_CODE       1
#define DELIMITER       " \""
#define ENVVARCHR          '$'

#define QUOTE_WRONG     1

int     ft_strccmp(char *s1, char *s2, char c);
t_list     *in_list(char *str, t_list *list);


typedef struct      s_env
{
    //for reading user input
    char        *buffer;
    int         buffer_size;
    int         buffer_count;

    //error codes and flags for exit message
    int         flags;
    int         error_message;
    
    //environment variables
    t_list      *environ;
    char        **environ_ptr;
    
    //Arguments from user and passed into programs
    t_list      *arguments;
    char        **argument_ptr;
    int         argument_count;
}   



#endif