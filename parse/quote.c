// 연결리스트의 이차원 배열을 돌기 -> 삼중반복문

#include "../includes/minishell.h"

// 이미 따옴표 검사 끝남 -> 따옴표 발견하면 지워주고 나머지는 내비둠 - 이때는 공백도 값이다.. 라고 봐야함. 
int parse_by_quote(t_cmd **start)
{
    int i;
    int j;
    t_cmd *tmp;

    tmp = (*start);
    while (tmp)
    {
        i = 0;
        while (tmp->arg->parse[i])
        {
            j = 0;
            while (tmp->arg->parse[i][j])
            {
                if (tmp->arg->parse[i][j] == '\'' || tmp->arg->parse[i][j] == '\"')
                {   
                    
                    tmp->arg->parse[i] = delete_char(&tmp->arg->parse[i], j, 1);
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