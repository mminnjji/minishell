/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:07:46 by man               #+#    #+#             */
/*   Updated: 2023/11/22 11:44:25 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

int	check_n(char *mod)
{
	int	i;

	i = 0;
	if (!mod || !mod[0])
		return (-1);
	while (mod[i])
	{
		if (mod[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	split_line(char *mod, int n, char *res, char *new_mod)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= n)
	{
		res[i] = mod[i];
		i++;
	}
	res[i] = 0;
	while (mod[i + j])
	{
		new_mod[j] = mod[i + j];
		j++;
	}
	ft_free(&mod);
	new_mod[j] = 0;
}

char	*get_res(char **mod, int n)
{
	char	*res;
	char	*new_mod;

	if (!ft_strlen(*mod))
	{
		ft_free(mod);
		return (NULL);
	}
	if (n == -1)
	{
		res = (*mod);
		(*mod) = 0;
		return (res);
	}
	res = (char *)malloc(n + 2);
	if (malloc_fail(res, NULL, mod, 3))
		return (NULL);
	new_mod = (char *)malloc(ft_strlen(*mod) - n);
	if (malloc_fail(new_mod, res, mod, 1))
		return (NULL);
	split_line(*mod, n, res, new_mod);
	(*mod) = new_mod;
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*mod = NULL;
	char		*buf;
	int			read_size;

	while (1)
	{
		buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (malloc_fail(buf, NULL, &mod, 3))
			return (NULL);
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == 0 || read_size == -1)
		{
			ft_free(&buf);
			if (malloc_fail(NULL, NULL, &mod, ((read_size != -1) + 3)))
				return (NULL);
			break ;
		}
		buf[read_size] = 0;
		mod = ft_strjoin(mod, buf);
		if (!mod)
			return (NULL);
		if (check_n(mod) >= 0)
			break ;
	}
	return (get_res(&mod, check_n(mod)));
}