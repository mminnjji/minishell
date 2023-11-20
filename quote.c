// 연결리스트의 이차원 배열을 돌기 -> 삼중반복문

#include "minishell.h"

int parse_by_quote(t_cmd **start)
{
    int i;
    int j;
    t_cmd *tmp;

    tmp = (*start);
    i = 0;
    while (tmp)
    {
        while (tmp->arg->parse[i][0])
        {
            j = 0;
            printf("%d tmp:%s\n", i, tmp->arg->parse[i]);
            while (tmp->arg->parse[i][j])
            {
                if (tmp->arg->parse[i][j] == '\'' || tmp->arg->parse[i][j] == '\"')
                {    
                    tmp->arg->parse[i] = delete_char(tmp->arg->parse[i], j);
                    j--;
                }
                j++;
            }
            i++;
        }
        tmp = tmp -> next;
    }
    return (0);
}