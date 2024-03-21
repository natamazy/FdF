/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_moves_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:51:50 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/21 15:38:31 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (x * (data->bits_per_pixel / 8) < 0)
		return ;
	if (x * (data->bits_per_pixel / 8) > data->line_length - 1)
		return ;
	if (dst >= data->addr && dst < data->addr + (1080 * data->line_length))
		*(unsigned int *) dst = color;
}

void	final_drawing(t_xyz *xyz, t_vars *vars)
{
	while ((int)(xyz->x - xyz->x1) || (int)(xyz->y - xyz->y1))
	{
		my_mlx_pixel_put(vars->img, (int) xyz->x, (int) xyz->y, vars->color);
		xyz->x += xyz->x_step;
		xyz->y += xyz->y_step;
	}
}

t_xyz	init_xyz(float x, float y, float x1, float y1)
{
	t_xyz	xyz;

	xyz.x = x;
	xyz.y = y;
	xyz.x1 = x1;
	xyz.y1 = y1;
	return (xyz);
}

void	draw(t_vars *vars)
{
	t_xyz	xyz;
	int		x;
	int		y;

	y = 0;
	while (y < vars->y_size)
	{
		x = 0;
		while (x < vars->x_size)
		{
			if (x < vars->x_size - 1)
			{
				xyz = init_xyz(x, y, x + 1, y);
				bresenham(xyz, vars);
			}
			if (y < vars->y_size - 1)
			{
				xyz = init_xyz(x, y, x, y + 1);
				bresenham(xyz, vars);
			}
			x++;
		}
		y++;
	}
}

void	coloring(t_xyz *xyz, t_vars *vars)
{
	if (vars->color_mode == 1)
	{
		vars->color = 0xffffff;
	}
	else if (vars->color_mode == 2)
	{
		if (xyz->z1 || xyz->z2)
			vars->color = 0x000000;
		else
			vars->color = 0x0000ff;
	}
	else
	{
		if (xyz->z1 || xyz->z2)
		{
			vars->color = random_color(vars->seed);
			vars->seed += 1;
		}
		else
			vars->color = 0xff00ff;
	}
}
