// 연결리스트의 이차원 배열을 돌기 -> 삼중반복문

#include "../includes/minishell.h"

int check_envp(t_cmd **start, char **envp)
{
    int i;
    int j;
    int flag;
    t_cmd *tmp;

    tmp = (*start);
    flag = 0;
    while (tmp)
    {
        i = -1;
        while (tmp->cmd[++i])
        {
            j = -1;
            while (tmp->cmd[i][++j])
            {
                if (tmp->cmd[i][j] == '\'')
                    flag = 1 - flag;
                if (tmp->cmd[i][j] == '$' && flag != 1)
                {
                    tmp->cmd[i] = replace_env(&(tmp->cmd[i]), j, envp, tmp->idx);
                    j--;
                }
            }
        }
        tmp = tmp -> next;
    }
    return (0);
}

// 이미 따옴표 검사 끝남 -> 따옴표 발견하면 지워주고 나머지는 내비둠 - 이때는 공백도 값이다.. 라고 봐야함. 
int parse_by_quote(t_cmd **start)
{
    int i;
    int j;
    t_cmd *tmp;

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
                {
                    tmp->cmd[i] = delete_char(&(tmp->cmd[i]), j, 1, 0);
                    j--;
                }
            }
        }
        tmp = tmp -> next;
    }
    return (0);
} 