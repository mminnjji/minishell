#include "minishell.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

char *check_heredoc(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
            break;
        i++;
    }
    if (!str[i])
        return (str);
    return (NULL);
}

t_cmd *get_cmd_list(char *str)
{
    int i;
    int count;
    int flag;
    t_cmd *start;
    t_cmd *tmp;

    i = -1;
    count = 0;
    flag = 0;
    start = malloc(sizeof(t_cmd));
    tmp = start;
    while (str[++i])
    {
        if (str[i] == '\"' || str[i] == '\'')
            flag = 1 - flag;
        if (str[i] == '|' && flag == 0)
            count++;
    }
    i = 0;
    while (i++ < count)
    {
        start->next = malloc(sizeof(t_cmd));
        start = start->next;
    }
    start->next = NULL;
    return (tmp);
}

void work_cmd(char *str)
{
    //char **tmp_str;
    t_cmd *start;

    start = get_cmd_list(str);
    //str = check_heredoc(str);

    //tmp_str = ft_split(str, ' ');

}

int main(void)
{
    char *str;

    while (1)
    {
        str = readline("minishell-3.2$ ");
        if (str)
            work_cmd(str);
        else
            break;
        add_history(str);
        free(str);
    }
    return (0);
}
