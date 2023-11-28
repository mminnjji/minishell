#include "../includes/minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// i 인덱스 문자 포함 n만큼 delete 하고 앞으로 당긴 새로운 문자열 생성
char *delete_char(char **str, int i, int n)
{
    int j;
    int k;
    char *res;

    res = malloc(sizeof(char) * (ft_strlen(*str) + 1));
    j = 0;
    k = 0;
    while ((*str)[j])
    {
        if (j == i)
            j = j + n;
        res[k] = (*str)[j];
        if (!(*str)[j])
            break;
        k++;
        j++;
    }
    res[k] = 0;
    //free((*str));
    return (res);
}

//따옴표 제거
char *remove_quote_env(char *str, char **envp, int idx)
{
    int i;
    int len;
    int count;

    i = 0;
    count = 0;
    len = ft_strlen(str);
    while (i <= len - count)
    {
        if (str[i] == '\"' || str[i] == '\'')
        {
            count++;
            str = delete_char(&str, i, 1);
            i--;
        }
        if (str[i] == '$')
        {
            str = replace_env(&str, i, envp, idx);
            i--;
        }
        i++;
    }
    return (str);
}

//진짜. 히어독 -> 스트링이랑 비교해서 같은게 있을 때 탈출시켜줌 -> 이전 문자열 임시파일 저장
int here_doc(char *str, int idx)
{
    int file;
    char *line;
    char *name;
    char *sstr;

    sstr = ".heredoc_tmp ";
    name = append_str2(&sstr, 12, ft_itoa(idx));
    unlink(name);
    file = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
    if (file < 0)
        return (1);
    while (1)
    {
        write(1, "heredoc> ", 9);
        line = get_next_line(0);
        if (!line)
            return (0);
        if (!ft_strncmp(str, line, ft_strlen(str)) && ft_strlen(str) == (ft_strlen(line) - 1))
            break;
        write(file, line, ft_strlen(line));
        free(line);
    }
    free(line);
    close(file);
    return (0);
}

char *get_heredoc(char *str, int n, int *len)
{
    int i;
    int j;
    int flag[2];
    char *res;

    i = 0;
    j = -1;
    flag[0] = 0;
    flag[1] = 0;
    while (str[n + i] && str[n + i] == ' ')
    {
        (*len)++;
        n++;
    }
    while (str[n + i])
    {
        if (str[n + i] == '\"' || str[n + i] == '\'')
            flag[str[n + i] % 2] = 1 - flag[str[n + i] % 2];
        if (flag[0] == 0 && flag[1] == 0 && str[n + i] == ' ')
            break;
        (*len)++;
        i++;
    }
    res = malloc(sizeof(char) * (i + 1));
    while (++j < i)
        res[j] = str[n + j];
    res[j] = 0;
    return (res);
}

int check_heredoc(t_cmd **start, int flag[], char **envp)
{
    int i;
    int len;
    t_cmd *tmp;
    char *str;

    tmp = (*start);
    len = 2;
    exit_code = 0;
    while (tmp)
    {
        i = 0;
        tmp->infile = 1; // stdin;
        tmp->outfile = 0; // stdout;
        while (tmp->init_cmd[i])
        {
            if (tmp->init_cmd[i] == '\"' || tmp->init_cmd[i] == '\'')
                flag[tmp->init_cmd[i] % 2] = 1 - flag[tmp->init_cmd[i] % 2];
            if (!ft_strncmp(tmp->init_cmd + i, "<<", 2) && flag[0] == 0 && flag[1] == 0)
            {
                str = get_heredoc(tmp->init_cmd, i + 2, &len);
                str = remove_quote_env(str, envp, tmp->idx);
                tmp->init_cmd = delete_char(&(tmp->init_cmd), i, len); // 히어독 없애버리기
                i = i - 1;
                here_doc(str, tmp->idx);
                char *sstr;

                sstr = ".heredoc_tmp ";
                char *name = append_str2(&sstr, 12, ft_itoa(tmp->idx));
                tmp->infile = open(name, O_RDONLY); // 일단! 인파일 fd열고 시작
            }
            i++;
        }
        tmp = tmp ->next;
    }
    return (0);
}
