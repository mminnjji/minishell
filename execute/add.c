/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 20:34:24 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/11 18:59:51 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(const char *s, char ch)
{
	int	i;

	i = 0;
	while (*(s + i) != ch)
	{
		if (*(s + i) == '\0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (*(str1 + i) && *(str2 + i))
	{
		if (*(str1 + i) > *(str2 + i))
			return (2);
		if (*(str1 + i) < *(str2 + i))
			return (1);
		i++;
	}
	if (*(str1 + i) > *(str2 + i))
		return (2);
	if (*(str1 + i) < *(str2 + i))
		return (1);
	return (0);
}

int	ft_strlen(char *s)
{
	int	size;

	size = 0;
	if (!s)
		return (0);
	while (*(s + size))
	{
		size++;
	}
	return (size);
}

int	ft_atoi(const char *nptr, int flag, int p, int answer)
{
	int	i;

	i = 0;
	if (!flag && (*(nptr + i) == '+' || *(nptr + i) == '-'))
		i++;
	if (!flag && !*(nptr + i))
		return (0);
	while (!flag && *(nptr + i))
	{
		if (*(nptr + i) > '9' || *(nptr + i) < '0')
			return (0);
		i++;
	}
	if (!flag)
		return (1);
	if (*(nptr + i) == '-')
		p = -1;
	if (*(nptr + i) == '-' || *(nptr + i) == '+')
		i++;
	while (*(nptr + i) >= '0' && *(nptr + i) <= '9')
	{
		answer = answer * 10 + *(nptr + i) - '0';
		i++;
	}
	return (answer * p);
}
