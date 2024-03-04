/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:20:57 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/11 18:59:51 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*key(char *env)
{
	int		i;
	char	*key;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (0);
	key[i] = 0;
	while (i--)
		key[i] = env[i];
	return (key);
}

char	*val(char *env)
{
	int		i;
	int		j;
	char	*val;

	i = 0;
	j = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (0);
	while (env[i + j])
		j++;
	val = (char *)malloc(sizeof(char) * (j + 1));
	if (!val)
		return (0);
	val[j] = 0;
	while (j--)
		val[j] = env[i + j];
	return (val);
}

void	change_env2(t_env **curr, char ***env, int flag, int *len)
{
	int	i;
	int	j;
	int	l;

	i = -1;
	j = -1;
	if ((*curr)->value || flag)
	{
		l = ft_strlen((*curr)->key) + ft_strlen((*curr)->value) + 1;
		(*env)[++(*len)] = (char *)malloc(l);
		if (!(*env)[*len])
		{
			ft_free(env);
			return ;
		}
		while ((*curr)->key && (*curr)->key[++i])
			(*env)[*len][i] = (*curr)->key[i];
		while ((*curr)->value && (*curr)->value[++j])
			(*env)[*len][i + j] = (*curr)->value[j];
		if (!(*curr)->value)
			j++;
		(*env)[*len][i + j] = 0;
	}
}

char	**change_env(t_env *envs, int flag, t_env *curr, int len)
{
	char	**env;
	int		l;

	l = -1;
	while (curr)
	{
		if (curr->key && (curr->value || flag))
			len++;
		curr = curr->next;
	}
	env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (0);
	while (++l <= len)
		env[l] = 0;
	if (len == 0)
		return (env);
	curr = envs;
	len = -1;
	while (curr)
	{
		change_env2(&curr, &env, flag, &len);
		curr = curr->next;
	}
	return (env);
}

t_env	*make_envs(char **env, t_env *envs)
{
	int	i;

	i = -1;
	if (!env[0])
		envs = ft_lstnew(0, 0, 0);
	while (env[++i])
	{
		if (!envs)
			envs = ft_lstnew(key(env[i]), val(env[i]), env[i]);
		else if (envs)
		{
			if (ft_lstadd_back(&envs, ft_lstnew(key(env[i]), \
			val(env[i]), env[i])))
			{
				ft_lstclear(&envs);
				return (0);
			}
		}
		if (!envs)
			return (0);
	}
	return (envs);
}
