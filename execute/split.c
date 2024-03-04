/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 04:00:33 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/11 18:59:51 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s, int l)
{
	int		i;
	char	*arr;

	i = 0;
	if (l != 0)
		i = l;
	else
		while (*(s + i))
			i++;
	arr = (char *)malloc(i + 1);
	if (!arr)
		return (0);
	*(arr + i) = 0;
	while (--i >= 0)
		*(arr + i) = *(s + i);
	return (arr);
}

static void	mk_arr(char const *s, char c, size_t *i, char *arr)
{
	size_t	j;

	j = 0;
	while (s[*i])
	{
		if (s[*i] != c)
		{
			arr[j++] = s[*i];
			*i += 1;
			if (s[*i] == c)
				break ;
		}
		else
			*i += 1;
	}
	arr[j] = 0;
}

static size_t	s_count(char const *s, char c, size_t *i)
{
	size_t	count;

	count = 0;
	while (s[*i])
	{
		if (s[*i] != c)
		{
			count++;
			*i += 1;
			if (s[*i] == c)
				break ;
		}
		else
			*i += 1;
	}
	return (count);
}

static size_t	count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (*(s + i))
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	arr = (char **)malloc(sizeof(char *) * (count(s, c) + 1));
	if (!arr)
		return (0);
	while (i < count(s, c))
	{
		arr[i] = (char *)malloc(s_count(s, c, &j) + 1);
		if (arr[i] == 0)
		{
			ft_free(&arr);
			return (0);
		}
		mk_arr(s, c, &k, *(arr + i));
		i++;
	}
	*(arr + i) = 0;
	return (arr);
}
