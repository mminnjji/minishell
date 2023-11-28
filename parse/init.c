#include "../includes/minishell.h"

t_cmd *init_node(int idx)
{
    t_cmd *node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return (NULL);
    node->init_cmd = NULL;
    node->cmd = NULL;
    node->infile = 1;
    node->outfile =  0;
    node->idx = idx;
    node->outfile_flag = 0;
    node->next = NULL;
    return (node);
}

int check_pipe_quote(char *str, char c) // 파이프와 따옴표 확인
{
    int i;
    int flag[2];
    int count;

    i = -1;
    count = 0;
    flag[0] = 0;
    flag[1] = 0;
    while (str[++i])
    {
        if (str[i] == '\"' || str[i] == '\'')
            flag[str[i] % 2] = 1 - flag[str[i] % 2];
        if (str[i] == c && flag[0] == 0 && flag[1] == 0) //따옴표 안이 아닐 경우
        {
            count++;
            while (str[i + 1] == ' ')
                i++;
            if (c == '|' && str[i + 1] == c) // 연속된 파이프가 등장할 경우
                return (-1);
        }
        if (flag[0] * flag[1] == 1) // 따옴표 안 닫혔는데 .. 새로 다른 따옴표 열렸을 경우
            return (-1);
    }
    if (flag[0] == 1 || flag[1] == 1) // 따옴표 안닫혔을 경우
        return (-1);
    return (count);
}

// 파이프 기준으로 연결리스트 할당
int get_malloc_list(char *str, t_cmd **start)
{
    int i;
    int count;
    t_cmd *tmp;

    tmp = *start;
    count = check_pipe_quote(str, '|'); // 파이프 개수 세기 - 따옴표/연속파이프 처리
    if (count < 0)
        return (-2);// syntax error
    i = 0;
    while (i++ < count)
    {
        tmp->next = init_node(i);
        if (!(tmp->next))
            return (-1); // start ~ 할당된 구조체 까지 free
        tmp = tmp->next;
    }
    return (count);
}