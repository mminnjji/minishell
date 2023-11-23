// 연결리스트의 이차원 배열을 돌기 -> 삼중반복문

#include "../includes/minishell.h"

char *replace_str(char **str, int j, char **envp, int flag[])
{
    if ((*str)[j] == '$' && flag[1] == 0)
        return (replace_env(str, j, envp)) ;
    if ((*str)[j] == '\'' || (*str)[j] == '\"')
        return (delete_char(str, j, 1));
    return (NULL);
}

// 이미 따옴표 검사 끝남 -> 따옴표 발견하면 지워주고 나머지는 내비둠 - 이때는 공백도 값이다.. 라고 봐야함. 
int parse_by_quote(t_cmd **start, char **envp)
{
    int i;
    int j;
    int flag[2];
    t_cmd *tmp;

    flag[0] = 0;
    flag[1] = 0;
    tmp = (*start);
    while (tmp)
    {
        i = -1;
        while (tmp->cmd[++i])
        {
            j = -1;
            while (tmp->cmd[i][++j])
            {
                if (tmp->cmd[i][j] == '\"' || tmp->cmd[i][j] == '\'')
                    flag[tmp->cmd[i][j] % 2] = 1 - flag[tmp->cmd[i][j] % 2];
                if (tmp->cmd[i][j] == '$' || tmp->cmd[i][j] == '\'' || tmp->cmd[i][j] == '\"')
                {
                    tmp->cmd[i] = replace_str(&tmp->cmd[i], j, envp, flag);
                    j--;
                }
            }
        }
        tmp = tmp -> next;
    }
    return (0);
} 