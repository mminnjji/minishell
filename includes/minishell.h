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

int exit_code; // $? 치환하는 종료코드


typedef struct s_cmd
{
    char *init_cmd;
    char **cmd;
    int infile;
    int outfile;
    int idx;
    int outfile_flag; // 0일때 그냥 입력 + 1일떄 추가입력
    struct s_cmd *next;
} t_cmd;


t_cmd *init_node(int idx);
char	**ft_split(char const *str, char c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
int parse_by_pipe(char *str, t_cmd **start, int pipe_n);
int get_malloc_list(char *str, t_cmd **start);
int parse_by_space(t_cmd **start);
int parse_by_quote(t_cmd **start);
int count_char(char *str, char c);
int count_str(char *str, char c);
int	ft_strncmp(char *s1, char *s2, size_t n);
char *delete_char(char **str, int i, int n, int flag);
char *remove_quote_env(char *str, char **envp, int idx);
int here_doc(t_cmd **tmp, char **envp, int flag[]);
char *get_heredoc(char *str, int n, int *len, int flag[]);
int check_heredoc(t_cmd **start, int flag[], char **envp);
int check_redirect(t_cmd **start, char **envp);
char *replace_env(char **str, int j, char **envp, int idx);
char	*ft_itoa(int n);
int check_envp(t_cmd **start, char **envp);
char *append_str2(char **str, int i, char *tmp);
int minishell_free(t_cmd **start);
int print_error(void);
int r_heredoc(char *str, int idx);
char *remove_quote_env_do_heredoc(t_cmd **tmp, char **envp, int flag[], int *i);

#endif