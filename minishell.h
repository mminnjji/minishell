#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmd
{
    char    **cmd;
    int infile;
    int outfile;
    int idx;
    int outfile_flag; // 0일때 그냥 입력 + 1일떄 추가입력
    int semi_flag; // 세미콜론의 등장 - 1이면 세미콜론 아니면 그냥 파이프
    struct s_cmd *next;
} t_cmd;

char	**ft_split(char const *str, char c);
#endif