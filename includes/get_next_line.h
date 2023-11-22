/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: man <man@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:28:32 by man               #+#    #+#             */
/*   Updated: 2023/11/20 14:30:59 by man              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

int		check_n(char *mod);
void	split_line(char *mod, int n, char *res, char *new_mod);
char	*get_res(char **mod, int n);
char	*get_next_line(int fd);
int		ft_strlen(char *str);
void	ft_free(char **str);
int		malloc_fail(char *str, char *one, char **two, int flag);
char	*ft_strjoin(char *mod, char *buf);

#endif