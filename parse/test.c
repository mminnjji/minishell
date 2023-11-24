char	*get_path(char **envp, char **str, int idx)
{
    int i;
    char *res;

    i = 0;
    res = ft_itoa(exit_code);
    if ((*str)[0] == '?')
    {
        if (idx == 0)
            return (res);
        else
            return ("0");
    }
	while (*envp)
    {
        while ((*str)[i])
        {
            if ((*envp)[i] != (*str)[i])
                break;
            i++;
        }
        if (i == ft_strlen((*str)))
        {
            if ((*envp)[i] == '=')
            {
                free(*str);
                return ((*envp) + i + 1);
            }
        }
		envp++;
    }
    free(*str);
    return ("");
}