#include "minishell.h"
//파이프 기준 파싱 -> 히어독 체크 -> 인아웃파일 넣기 (cmd 제외 날리기)-> 공백관련 스플릿 -> 따옴표 없애기
int check_redirect_in(t_cmd **tmp)
{
    int i;
    char *str;

    i = 0;
    while ((*tmp)->arg->init_cmd[i])
    {
        if ((*tmp)->arg->init_cmd[i] == '<' && ft_strncmp((*tmp)->arg->init_cmd + i, "<<", 2))
        {
            printf("comeon\n");
            str = get_heredoc((*tmp)->arg->init_cmd, i + 1);
            str = remove_quote(str);
            (*tmp)->arg->init_cmd = delete_char((*tmp)->arg->init_cmd, i, strlen(str) + 1);
            (*tmp)->infile = open(str, O_RDONLY);
            printf("str : %s\n", str);
            if ((*tmp)->infile < 0)
                return (1);
            printf("str : %s\n", str);
            i = i + ft_strlen(str) + 1;
        }
        i++;
    }
    return (0);
}

int check_redirect_out(t_cmd **tmp)
{
    int i;
    char *str;

    i = 0;
    while ((*tmp)->arg->init_cmd[i])
    {
        if ((*tmp)->arg->init_cmd[i] == '>' && ft_strncmp((*tmp)->arg->init_cmd + i, ">>", 2))
        {
            str = get_heredoc((*tmp)->arg->init_cmd, i + 1);
            str = remove_quote(str);
            (*tmp)->arg->init_cmd = delete_char((*tmp)->arg->init_cmd, i, strlen(str) + 1);
            (*tmp)->outfile = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
            if ((*tmp)->infile < 0)
                return (1);
        }
        i++;
    }
    return (0);
}

int check_redirect(t_cmd **start)
{
    t_cmd *tmp;

    tmp = (*start);
    check_heredoc(start);
    while (tmp)
    {
        if (check_redirect_in(&tmp))
            return (1);
        if (check_redirect_out(&tmp))
            return (1);
        tmp = tmp->next;
    }
    return (0);
}