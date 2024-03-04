/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:21:06 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/11 18:59:51 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear(t_env **lst)
{
	t_env	*temp;

	if (!lst || !(*lst))
		return ;
	while ((*lst)->next)
	{
		temp = *lst;
		free((*lst)->key);
		if ((*lst)->value)
			free((*lst)->value);
		(*lst) = temp->next;
		free(temp);
	}
	free((*lst)->key);
	if ((*lst)->value)
		free((*lst)->value);
	free(*lst);
	(*lst) = 0;
}

t_env	*ft_lstnew(char *c_key, char *c_val, char *check)
{
	t_env	*envs;

	if (!check)
	{
		envs = (t_env *)malloc(sizeof(t_env));
		if (!envs)
			return (0);
		envs->key = 0;
		envs->value = 0;
		envs->next = 0;
		return (envs);
	}
	if (ft_strchr(check, '=') && !c_val)
		return (0);
	if (!c_key)
		return (0);
	envs = (t_env *)malloc(sizeof(t_env));
	if (!envs)
		return (0);
	envs->key = c_key;
	envs->value = c_val;
	envs->next = 0;
	return (envs);
}

int	ft_lstadd_back(t_env **lst, t_env *new_env)
{
	t_env	*curr;

	curr = *lst;
	if (!lst || !new_env)
		return (1);
	if (!(*lst))
	{
		*lst = new_env;
		return (0);
	}
	if (!(*lst)->key || (*lst)->key[0] == 0)
	{
		free (*lst);
		*lst = new_env;
		return (0);
	}
	while (curr->next)
		curr = curr->next;
	curr->next = new_env;
	return (0);
}

void	sort(char **env)
{
	int		i;
	int		j;
	char	*temp;
	int		count;

	count = 0;
	while (env[count])
		count++;
	j = 0;
	while (j < count - 1)
	{
		i = 0;
		while (i < count - j - 1)
		{
			if (ft_strcmp(env[i], env[i + 1]) > 1)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
}

char	*find_key(t_env *envs, char *key)
{
	t_env	*curr;

	curr = envs;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
			return (curr->value);
		curr = curr->next;
	}
	return (0);
}
