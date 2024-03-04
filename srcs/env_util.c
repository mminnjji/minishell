/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:05:10 by man               #+#    #+#             */
/*   Updated: 2023/12/21 12:41:01 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*append_str2(char **str, int i, char *tmp)
{
	int		j;
	int		k;
	char	*res;

	j = 0;
	k = 0;
	res = malloc(sizeof(char) * (ft_strlen(*str) + ft_strlen(tmp) + 1));
	while ((*str)[j])
	{
		if (j == i)
		{
			while (tmp[k])
			{
				res[j + k] = tmp[k];
				k++;
			}
		}
		res[j + k] = (*str)[j];
		j++;
	}
	res[j + k] = 0;
	ft_free2((void **)&tmp);
	return (res);
}

char	*append_str(char **str, int i, char *tmp)
{
	int		j;
	int		k;
	char	*res;

	j = 0;
	k = 0;
	res = malloc(sizeof(char) * (ft_strlen(*str) + ft_strlen(tmp) + 1));
	while (((*str)[j] || tmp[k]))
	{
		if (j == i)
		{
			while (tmp[k])
			{
				res[j + k] = tmp[k];
				k++;
			}
		}
		if (!(*str)[j] && !tmp[k])
			break ;
		res[j + k] = (*str)[j];
		j++;
	}
	res[j + k] = 0;
	ft_free2((void **)str);
	return (res);
}

char	*delete_char(char **str, int i, int n, int flag)
{
	int		j;
	int		k;
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(*str) + 1));
	if (!res)
		return (NULL);
	j = 0;
	k = 0;
	while ((*str)[j])
	{
		if (j == i)
			j = j + n;
		res[k] = (*str)[j];
		if (!(*str)[j])
			break ;
		k++;
		j++;
	}
	res[k] = 0;
	if (!flag)
		ft_free2((void **)str);
	return (res);
}

char	*get_path_q(int idx)
{
	char	*res;

	res = ft_itoa(g_exit_code);
	if (idx != 0)
		ft_strlcpy(res, "0", 2);
	return (res);
}
