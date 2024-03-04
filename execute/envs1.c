/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiheekan <jiheekan@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:03:27 by jiheekan          #+#    #+#             */
/*   Updated: 2023/11/27 21:03:28 by jiheekan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	same_key2(t_env *curr, char **c_key, char **c_val)
{
	while (curr)
	{
		if (!ft_strcmp(*c_key, curr->key))
		{
			if (*c_val)
			{
				if (curr->value)
					free(curr->value);
				curr->value = *c_val;
			}
			free(*c_key);
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	same_key(char *cmd, t_env *curr)
{
	char	*c_key;
	char	*c_val;

	if (!curr->key)
	{
		free(cmd);
		return (0);
	}
	c_key = key(cmd);
	if (!c_key)
		return (-1);
	c_val = val(cmd);
	if (!c_val && ft_strchr(cmd, '='))
		free(c_key);
	if (!c_val && ft_strchr(cmd, '='))
		return (-1);
	free(cmd);
	if (same_key2(curr, &c_key, &c_val))
		return (1);
	free (c_key);
	if (c_val)
		free (c_val);
	return (0);
}

void	check_export(char **cmd, int i, int j)
{
	while (cmd[++i])
	{
		if ((cmd[i][0] >= '0' && cmd[i][0] <= '9') || cmd[i][0] == '=' ||
		(!ft_strcmp(cmd[0], "unset") && ft_strchr(cmd[i], '=')) || !cmd[i][0])
		{
			write(2, "not a valid identifier\n", 23);
			cmd[i][0] = '=';
			g_exit_code = 1;
			continue ;
		}
		j = -1;
		while (cmd[i][++j] && cmd[i][j] != '=')
		{
			if ((cmd[i][j] > 57 || cmd[i][j] < 48) && (cmd[i][j] > 90 || \
			cmd[i][j] < 65) && (cmd[i][j] > 122 || cmd[i][j] < 97) \
			&& cmd[i][j] != '_')
			{
				write(2, "not a valid identifier\n", 23);
				cmd[i][0] = '=';
				g_exit_code = 1;
				break ;
			}
		}
	}
}

void	delete_envs2(t_env **curr, char *c_key, t_env **envs, t_env **before)
{
	if (!strcmp((*curr)->key, c_key))
	{
		if (!(*before))
		{
			*curr = *envs;
			*envs = (*envs)->next;
		}
		else
			(*before)->next = (*curr)->next;
		free((*curr)->key);
		if ((*curr)->value)
			free((*curr)->value);
		free(*curr);
		*curr = 0;
		if (!(*envs))
			(*envs) = ft_lstnew(0, 0, 0);
		return ;
	}
	if (!(*before))
		*before = *envs;
	else
		*before = *curr;
}

void	delete_envs(char *cmd, t_env **envs, t_env *for_curr, char *c_key)
{
	t_env	*curr;
	t_env	*before;

	if (cmd[0] == '=')
		return ;
	c_key = key(cmd);
	curr = for_curr;
	before = 0;
	while (curr)
	{
		delete_envs2(&curr, c_key, envs, &before);
		if (curr)
			curr = curr->next;
	}
	free(c_key);
}
