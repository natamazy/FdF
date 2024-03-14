/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:20:05 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/14 11:54:07 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/get_next_line.h"

int	argc_and_filename_validation(int argc, char **argv)
{
	int	len;

	if (argc != 2)
	{
		ft_putstr_fd("Invalid arguments count.\n", 2);
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strcmp(&(argv[1][len - 4]), ".fdf") != 0)
	{
		ft_putstr_fd("Invalid filename or extention.\n", 2);
		ft_putstr_fd("Usage: ./fdf <name>.fdf\n", 2);
		return (1);
	}
	return (0);
}

int	**parsing(int fd)
{
	char	*row;
	char	**row_splited;

	row = get_next_line(fd);
	if (row == NULL)
	{
		ft_putstr_fd("Invalid map.\n", 2);
		return (NULL);
	}
	row_splited = ft_split(row, " \t\v\f\r\n");
	return (NULL);
}

int	validation(int argc, char **argv, t_vars *vars)
{
	int	fd;

	if (argc_and_filename_validation(argc, argv) == 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("File opening failed.\n", 2);
		return (1);
	}
	vars->map = parsing(fd);
	close(fd);
	return (0);
}