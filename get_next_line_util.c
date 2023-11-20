/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:07:50 by man               #+#    #+#             */
/*   Updated: 2023/11/20 14:30:44 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	ft_free(char **str)
{
	if (!(*str))
		return ;
	free(*str);
	(*str) = NULL;
}

int	malloc_fail(char *str, char *one, char **two, int flag)
{
	if (!str && flag == 1)
	{
		ft_free(&one);
		ft_free(two);
		return (1);
	}
	if (!str && flag == 2)
	{
		ft_free(&one);
		return (1);
	}
	if (!str && flag == 3)
	{
		ft_free(two);
		return (1);
	}
	return (0);
}

char	*ft_strjoin(char *mod, char *buf)
{
	char	*new_mod;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_mod = (char *)malloc(ft_strlen(mod) + ft_strlen(buf) + 1);
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
	ft_free(&mod);
	ft_free(&buf);
	return (new_mod);
}