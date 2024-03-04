/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:42:05 by man               #+#    #+#             */
/*   Updated: 2023/12/18 16:25:01 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_strerr(char *str, int i)
{
	int	tmp;
	int	count;

	count = 0;
	tmp = i;
	if (str[i])
	{
		while (str[tmp] == '<' || str[tmp] == '>')
			tmp++;
		if (tmp - i >= 2)
			return (1);
		while (str[i] == ' ')
		{
			count++;
			i++;
		}
		if (!str[i] || str[i] == '|' || \
		(count != 0 && (str[i] == '<' || str[i] == '>')))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	init_error(t_cmd *tmp)
{
	int	i;

	while (tmp)
	{
		i = 0;
		while (tmp->init_cmd[i])
		{
			if (tmp->init_cmd[i] == '<' || tmp->init_cmd[i] == '>')
			{
				if (check_strerr(tmp->init_cmd, i + 1))
					return (3);
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
