/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:04:11 by man               #+#    #+#             */
/*   Updated: 2023/12/11 18:59:51 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	int_len(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		++count;
	}
	return (count);
}

static char	*make_str(char *str, int len, int n, int j)
{
	int	i;

	i = 1;
	while (len > 1)
	{
		i *= 10;
		len--;
	}
	while (i > 0)
	{
		str[j] = (n / i) % 10 + '0';
		i = i / 10;
		j++;
	}
	str[j] = 0;
	return (str);
}

static void	*check_str(char *str, int flag)
{
	if (flag)
	{
		str[10] = '8';
		str[11] = 0;
	}
	return (str);
}

static void	init_int(int *n, int *len, int *flag)
{
	*n = 214748364;
	(*len)--;
	*flag = 1;
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		j;
	int		flag;

	j = 0;
	flag = 0;
	len = int_len(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	if (n < 0)
	{
		if (n == -2147483648)
			init_int(&n, &len, &flag);
		else
			n *= -1;
		str[0] = '-';
		j++;
		len--;
	}
	str = make_str(str, len, n, j);
	return (check_str(str, flag));
}
