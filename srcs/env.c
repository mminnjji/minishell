/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:05:14 by man               #+#    #+#             */
/*   Updated: 2023/12/22 12:02:49 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char **envp, char **str, int idx)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	if ((*str)[0] == '?')
		return (get_path_q(idx));
	while (envp[++i])
	{
		j = -1;
		while ((*str)[++j])
			if (envp[i][j] != (*str)[j])
				break ;
		if (j == ft_strlen((*str)))
		{
			if (envp[i][j] == '=')
				return (delete_char(&envp[i], 0, j + 1, 1));
		}
	}
	res = malloc(sizeof(char) * 1);
	res[0] = 0;
	return (res);
}

char	*get_env(char *str, int j, int tmp)
{
	int		i;
	char	*env;

	i = -1;
	env = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!env)
		return (NULL);
	if (str[j + 1] == '?' || (str[j + 1] > 47 && str[j + 1] < 58))
	{
		env[0] = str[j + 1];
		env[1] = 0;
	}
	while (str[++j])
	{
		if (!((str[j] > 64 && str[j] < 91) || (str[j] > 96 && str[j] < 123) \
		|| (str[j] > 47 && str[j] < 58) || str[j] == '_'))
			break ;
	}
	if (env[0] != '?' && !(env[0] > 47 && env[0] < 58))
	{
		while (++tmp < j)
			env[++i] = str[tmp];
		env[++i] = 0;
	}
	return (env);
}

char	*replace_env(char **str, int j, char **envp, int idx)
{
	char	*env;
	char	*rep;
	int		len;

	env = get_env((*str), j, j);
	if (!env)
		return (NULL);
	len = ft_strlen(env);
	rep = get_path(envp, &env, idx);
	if (!rep)
		return (NULL);
	ft_free2((void **)&env);
	(*str) = delete_char(str, j, len + 1, 0);
	if (!(*str))
		return (NULL);
	(*str) = append_str(str, j, rep);
	ft_free2((void **)&rep);
	if (!(*str))
		return (NULL);
	return (*str);
}

int	check_envp_util(t_cmd **tmp, char **envp, int *j, int flag[])
{
	char	*str;

	str = (*tmp)->init_cmd;
	check_flag(str, flag, *j);
	if (((*tmp)->init_cmd[*j] == '$' && flag[1] != 1) \
	&& !(((*tmp)->init_cmd[(*j) + 1] == '\"' && flag[0]) || \
	((*tmp)->init_cmd[(*j) + 1] == ' ') || !((*tmp)->init_cmd[(*j) + 1])) \
	&& (((*tmp)->init_cmd[(*j) + 1] > 64 && (*tmp)->init_cmd[(*j) + 1] < 91) || \
	((*tmp)->init_cmd[(*j) + 1] > 96 && (*tmp)->init_cmd[(*j) + 1] < 123) \
	|| ((*tmp)->init_cmd[(*j) + 1] > 47 && (*tmp)->init_cmd[(*j) + 1] < 58) || \
	(*tmp)->init_cmd[(*j) + 1] == '_' || (*tmp)->init_cmd[(*j) + 1] == '?'))
	{
		(*tmp)->init_cmd = replace_env(&((*tmp)->init_cmd), \
		(*j), envp, (*tmp)->idx);
		if (!(*tmp)->init_cmd)
			return (1);
		(*j)--;
	}
	return (0);
}

int	check_envp(t_cmd **start, char **envp)
{
	int		j;
	t_cmd	*tmp;
	int		flag[2];

	tmp = (*start);
	flag[0] = 0;
	flag[1] = 0;
	while (tmp)
	{
		j = -1;
		while (tmp->init_cmd[++j])
		{
			if (check_envp_util(&tmp, envp, &j, flag))
				return (1);
		}
		tmp = tmp -> next;
	}
	return (0);
}
