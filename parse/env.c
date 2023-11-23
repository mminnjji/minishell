#include "../includes/minishell.h"

char	*get_path(char **envp, char *str)
{
    int i;

    i = 0;
	while (*envp)
    {
        while (str[i])
        {
            if ((*envp)[i] != str[i])
                break;
            i++;
        }
        if (i == ft_strlen(str))
        {
            if ((*envp)[i] == '=')
                return ((*envp) + i + 1);
        }
		envp++;
    }
    return (NULL);
}

int replace_env(t_cmd **start, char **envp)
{
    // 정리된 이차원배열을 돌면서 환경변수인 녀석 발견하기
    //어????????????????????????????????
    //따옴표랑 동시에 해야하네
    //ㅋㅋ.개망햇는데
}