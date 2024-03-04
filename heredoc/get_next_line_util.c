/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:07:50 by man               #+#    #+#             */
/*   Updated: 2023/12/13 10:35:48 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include "../minishell.h"

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_free2(void **str)
{
	if (!(*str))
		return (1);
	free(*str);
	(*str) = NULL;
	return (1);
}

int	malloc_fail(char *str, char *one, char **two, int flag)
{
	if (!str && flag == 1)
	{
		ft_free2((void **)&one);
		ft_free2((void **)two);
		g_exit_code = 1;
		return (1);
	}
	if (!str && flag == 2)
	{
		ft_free2((void **)&one);
		g_exit_code = 1;
		return (1);
	}
	if (!str && flag == 3)
	{
		ft_free2((void **)two);
		g_exit_code = 1;
		return (1);
	}
	return (0);
}

char	*ft_strjoin2(char *mod, char *buf)
{
	char	*new_mod;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_mod = (char *)malloc(ft_strlen2(mod) + ft_strlen2(buf) + 1);
	if (malloc_fail(new_mod, buf, &mod, 1))
		return (NULL);
	while (mod && mod[i])
	{
		new_mod[i] = mod[i];
		i++;
	}
	while (buf[j])
	{
		new_mod[i + j] = buf[j];
		j++;
	}
	new_mod[i + j] = 0;
	ft_free2((void **)&mod);
	ft_free2((void **)&buf);
	return (new_mod);
}
