/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_arr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 19:09:34 by jiheekan          #+#    #+#             */
/*   Updated: 2023/12/11 18:59:51 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(char ***arr)
{
	int	j;

	j = -1;
	if (!*arr)
		return ;
	while ((*arr)[++j])
		free((*arr)[j]);
	free(*arr);
	*arr = 0;
}

char	**d_strdup(char **s, int z)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = -1;
	while (s[i])
		i++;
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (arr == 0)
		return (0);
	while (++z <= i)
		arr[z] = 0;
	while (i - 1 >= ++j)
	{
		arr[j] = ft_strdup(s[j], ft_strlen(s[j]));
		if (!arr[j])
		{
			ft_free(&arr);
			return (0);
		}
	}
	return (arr);
}
