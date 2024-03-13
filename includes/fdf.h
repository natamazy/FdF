/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:25:58 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/13 19:54:55 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_vars
{
	int	**map;
	int	x_size;
	int	y_size;
}	t_vars;

// Functions in ft_putstr_fd.c
void	ft_putstr_fd(char *s, int fd);

// Functions in ft_strlen.c
size_t	ft_strlen(const char *s);

// Functions in ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);

// Functions in validation.c
int		validation(int argc, char *argv[], t_vars *vars);

#endif