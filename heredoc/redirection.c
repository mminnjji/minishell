#include "../includes/minishell.h"
//파이프 기준 파싱 -> 히어독 체크 -> 인아웃파일 넣기 (cmd 제외 날리기)-> 공백관련 스플릿 -> 따옴표 없애기
int check_redirect_in(t_cmd **tmp, int flag[], char **envp)
{
    int i;
    int len;
    char *str;

    i = 0;
    len = 1;
    while ((*tmp)->init_cmd[i])
    {
        if ((*tmp)->init_cmd[i] == '\"' || (*tmp)->init_cmd[i] == '\'')
            flag[(*tmp)->init_cmd[i] % 2] = 1 - flag[(*tmp)->init_cmd[i] % 2];
        if ((*tmp)->init_cmd[i] == '<' && flag[0] == 0 && flag[1] == 0)
        {
            str = get_heredoc((*tmp)->init_cmd, i + 1, &len, flag);
            str = remove_quote_env(str, envp, (*tmp)->idx);
            (*tmp)->init_cmd = delete_char(&((*tmp)->init_cmd), i, len);
            i = i - 1;
            (*tmp)->infile = open(str, O_RDONLY);
            if ((*tmp)->infile < 0)
                return (1);
        }
        i++;
    }
    return (0);
}


int check_redirect_out(t_cmd **tmp, int flag[], char **envp)
{
    int i;
    char *str;
    int len;

    i = 0;
    len = 1;
    while ((*tmp)->init_cmd[i])
    {
        if ((*tmp)->init_cmd[i] == '\"' || (*tmp)->init_cmd[i] == '\'')
            flag[(*tmp)->init_cmd[i] % 2] = 1 - flag[(*tmp)->init_cmd[i] % 2];
        if ((*tmp)->init_cmd[i] == '>' && flag[0] == 0 && flag[1] == 0)
        {
            str = get_heredoc((*tmp)->init_cmd, i + 1, &len, flag);
            str = remove_quote_env(str, envp, (*tmp)->idx);
            (*tmp)->init_cmd = delete_char(&((*tmp)->init_cmd), i, len);
            i = i - 1;
            (*tmp)->outfile = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
            if ((*tmp)->outfile < 0)
                return (1);
        }
        i++;
    }
    return (0);
}


int check_predirect(t_cmd **start, int flag[], char **envp)
{
    int i;
    int len;
    t_cmd *tmp;
    char *str;

    tmp = (*start);
    len = 2;
    while (tmp)
    {
        i = 0;
        tmp->outfile_flag = 0;
        while (tmp->init_cmd[i])
        {
            if (tmp->init_cmd[i] == '\"' || tmp->init_cmd[i] == '\'')
                flag[tmp->init_cmd[i] % 2] = 1 - flag[tmp->init_cmd[i] % 2];
            if (!ft_strncmp(tmp->init_cmd + i, ">>", 2) && flag[0] == 0 && flag[1] == 0)
            {
                str = get_heredoc(tmp->init_cmd, i + 2, &len, flag);
                str = remove_quote_env(str, envp, tmp->idx);
                tmp->init_cmd = delete_char(&(tmp->init_cmd), i, len); // 히어독 없애버리기
                i = i - 1;
                tmp->outfile = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
                if (tmp->outfile < 0)
                    return (1);
                tmp->outfile_flag = 1;
            }
            i++;
        }
        tmp = tmp ->next;
    }
    return (0);
}

void	delete_node(t_cmd **cur_lst, t_cmd **origin)
{
	t_cmd	*prev_node;
	t_cmd	*current_node;

	prev_node = NULL;
	current_node = *origin;
	if (*cur_lst == NULL || origin == NULL || *origin == NULL)
		return ;
	while (current_node != NULL)
	{
		if (current_node == (*cur_lst))
			break ;
		prev_node = current_node;
		current_node = current_node->next;
	}
	if (current_node == NULL)
		return ;
	if (prev_node == NULL)
		*origin = current_node->next;
	else
		prev_node->next = current_node->next;
    free(current_node->init_cmd);
	free(current_node);
}

int check_redirect(t_cmd **start, char **envp)
{
    t_cmd *tmp;
    int flag[2];

    tmp = (*start);
    flag[0] = 0;
    flag[1] = 0;
    check_heredoc(start, flag, envp);
    while (tmp)
    {
        if (check_redirect_in(&tmp, flag, envp))
        {
            delete_node(&tmp, start);
            perror("Error");
            tmp = (*start);
        }
        else
            tmp = tmp->next;
    }
    check_predirect(start, flag, envp);
    tmp = (*start);
    while (tmp)
    {
        check_redirect_out(&tmp, flag, envp);
        tmp = tmp->next;
    }
    return (0);
}