#include "../includes/minishell.h"

int work_cmd(char *str, char **envp)
{
    t_cmd *start;
    int pipe_count;

    start = init_node(0);
    if (!start)
        print_error();
    pipe_count = get_malloc_list(str, &start); //구조체 할당
    if (pipe_count == -2)
        return (write(2, "syntax error\n", 13));
    if (pipe_count == -1)
        return (minishell_free(&start));
    if (parse_by_pipe(str, &start, pipe_count))
        return (minishell_free(&start));
    if (check_redirect(&start, envp))
        return (minishell_free(&start));
    parse_by_space(&start);
    check_envp(&start, envp);
    parse_by_quote(&start);
    while (start)
    {
        int i = 0;
        while (start->cmd[i])
        {
            printf("[%d]: %s\n", i, start->cmd[i]);
            i++;
        }
        printf("cmd : %s in : %d, out : %d\n", start->init_cmd, start->infile, start->outfile);
        start = start->next;
    }
    minishell_free(&start);
    return (0);
}

int main(int argc, char **argv, char *envp[])
{
    char *str;
    argc = 1;
    (void)argv;

    while (1)
    {
        str = readline("minishell ⋆◡̎⋆ 1.0 $ "); //문자열 받아서 실행
        if (str)
            work_cmd(str, envp);
        else
            break;
        add_history(str);
        free(str);
    }
    return (0);
}