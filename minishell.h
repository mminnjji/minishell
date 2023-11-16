#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_arg
{
    char *init_cmd;
    char **parse;
    char **f_parse;
} t_arg;

typedef struct s_cmd
{
    struct s_arg *arg;
    char    **cmd;
    int infile;
    int outfile;
    int idx;
    int outfile_flag; // 0일때 그냥 입력 + 1일떄 추가입력
    struct s_cmd *next;
} t_cmd;

char	**ft_split(char const *str, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int get_init_cmd_list(char *str, t_cmd *start, int pipe_n);
int get_malloc_list(char *str, t_cmd *start);

#endif