#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

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
int parse_by_space(t_cmd **start, int pipe_n);
int parse_by_quote(t_cmd **start);
int check_quote(char *str, char c);
int check_quote_2(char *str, char c);
int	ft_strncmp(char *s1, char *s2, size_t n);
char *delete_char(char *str, int i, int n);
char *remove_quote(char *str);
int here_doc(char *str);
char *get_heredoc(char *str, int n);
int check_heredoc(t_cmd **start);
int check_redirect(t_cmd **start);

#endif