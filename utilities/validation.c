/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:20:05 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/14 13:45:29 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/get_next_line.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

int	*convert_line(char **row_splited, int line_len)
{
	int	*ret_arr;
	int	i;

	i = 0;
	ret_arr = malloc(sizeof(int) * line_len);
	if (ret_arr == NULL)
	{
		ft_putstr_fd("Allocation failed.\n", 2);
		return (NULL);
	}
	while (row_splited[i])
	{
		ret_arr[i] = ft_atoi(row_splited[i]);
		i++;
	}
	return (ret_arr);
}

int	parsing_first_line(int fd, t_vars *vars)
{
	char	*row;
	char	**row_splited;

	row = get_next_line(fd);
	row_splited = ft_split(row, " \t\v\f\r\n");
	vars->x_size = ft_array_len(row_splited);
	vars->y_size = 1;
	vars->map = malloc(sizeof(int *) * (vars->y_size + 1));
	vars->map[0] = convert_line(row_splited, vars->x_size);
	vars->map[1] = NULL;
	free(row);
	free_array(row_splited);
	return (0);
}

int	parsing_other_lines(int fd, t_vars *vars)
{
	char	*row;
	char	**row_splited;
	int		row_length;
	int		j;

	while (1)
	{
		j = 0;
		row = get_next_line(fd);
		if (row == NULL)
			break;
		row_splited = ft_split(row, " \t\v\f\r\n");
		row_length = ft_array_len(row_splited);
		if (row_length != vars->x_size)
		{
			printf("ARA YNGER\n");
			break; // means that new line is not equal to old line
		}
		vars->y_size++;
		vars->temp_map = vars->map;
		vars->map = malloc(sizeof(int *) * (vars->y_size + 1));
		while (j < vars->y_size - 1)
		{
			vars->map[j] = vars->temp_map[j];
			j++;
		}
		vars->map[vars->y_size - 1] = convert_line(row_splited, row_length);
		vars->map[vars->y_size] = NULL;
		vars->temp_map = NULL;
		free_array(row_splited);
		free(row);
	}
	// free(row);
	// free_array(row_splited);
	return (0);
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
	if (parsing_first_line(fd, vars) == 1)
		return (1); //if failed
	parsing_other_lines(fd, vars);
	close(fd);
	return (0);
}
