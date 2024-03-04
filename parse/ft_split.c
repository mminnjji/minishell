/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 10:53:47 by man               #+#    #+#             */
/*   Updated: 2023/12/11 18:59:51 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_ac_util(char const *str, int *i, int flag[], char c)
{
	(*i)++;
	while (str[(*i)] && (str[(*i)] != c || \
	(str[(*i)] == c && (flag[0] == 1 || flag[1] == 1))))
	{
		if (str[(*i)] == '\"' || str[(*i)] == '\'')
			flag[str[(*i)] % 2] = 1 - flag[str[(*i)] % 2];
		(*i)++;
	}
}

static int	get_ac(char const *str, char c)
{
	int	i;
	int	count;
	int	flag[2];

	count = 0;
	i = 0;
	flag[0] = 0;
	flag[1] = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] == '\"' || str[i] == '\'')
			flag[str[i] % 2] = 1 - flag[str[i] % 2];
		if (str[i] && (str[i] != c || \
		(str[i] == c && (flag[0] == 1 || flag[1] == 1))))
		{
			count++;
			get_ac_util(str, &i, flag, c);
		}
	}
	return (count);
}

static char	*get_len(char const *str, char c, int *k, int *tmp)
{
	char	*res;
	int		flag[2];

	flag[0] = 0;
	flag[1] = 0;
	while (str[*k] == c)
		(*k)++;
	if (str[*k] == '\"' || str[*k] == '\'')
	flag[str[*k] % 2] = 1 - flag[str[*k] % 2];
	*tmp = *k;
	while (str[*k] && (str[*k] != c || \
	(str[*k] == c && (flag[0] == 1 || flag[1] == 1))))
	{
		(*k)++;
		if (str[*k] && (str[*k] == '\"' || str[*k] == '\''))
			flag[str[*k] % 2] = 1 - flag[str[*k] % 2];
	}
	res = (char *)malloc(sizeof(char) * (*k - *tmp + 1));
	return (res);
}

static char	*get_str(char const *str, int k, int tmp, char *res)
{
	int	j;

	j = 0;
	while (j < k - tmp)
	{
		res[j] = str[j + tmp];
		j++;
	}
	res[j] = 0;
	return (res);
}

char	**ft_split2(char const *str, char c)
{
	char	**res;
	int		tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	res = (char **)malloc((get_ac(str, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < get_ac(str, c) && str[k])
	{
		res[i] = get_len(str, c, &k, &tmp);
		if (!res[i])
			return (ft_freee(res));
		res[i] = get_str(str, k, tmp, res[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}
