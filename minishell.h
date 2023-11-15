#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_arg
{
    char *first_cmd;
    char **first_parse;
    char **second_parse;
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
#endif