/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:33:49 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/19 13:03:27 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"

#include <math.h>

void	isometric(float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = (*x + *y) * sin(angle) - z;
}

void	isometric_two_coordinates(t_xyz *xyz, float angle, t_vars *vars)
{
	if (vars->top_view == 1)
		return ;
	isometric(&(xyz->x), &(xyz->y), xyz->z1, angle);
	isometric(&(xyz->x1), &(xyz->y1), xyz->z2, angle);
}

float	float_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	shifting(t_xyz *xyz, t_vars *vars)
{
	xyz->x += vars->shift;
	xyz->y += vars->shift;
	xyz->x1 += vars->shift;
	xyz->y1 += vars->shift;
}

void	zooming(t_xyz *xyz, t_vars *vars)
{
	xyz->x *= vars->zoom;
	xyz->y *= vars->zoom;
	xyz->x1 *= vars->zoom;
	xyz->y1 *= vars->zoom;
}

void	init_z(t_xyz *xyz, t_vars *vars)
{
	xyz->z1 = vars->map[(int)xyz->y][(int)xyz->x];
	xyz->z2 = vars->map[(int)xyz->y1][(int)xyz->x1];
	if (xyz->z1 > 0)
		xyz->z1 += vars->z_zoom;
	if (xyz->z2 > 0)
		xyz->z2 += vars->z_zoom;
}

void	init_step(t_xyz *xyz)
{
	xyz->x_step = xyz->x1 - xyz->x;
	xyz->y_step = xyz->y1 - xyz->y;
}

void	init_max(t_xyz *xyz, t_vars *vars)
{
	if (float_abs(xyz->x_step) > float_abs(xyz->y_step))
		vars->max = float_abs(xyz->x_step);
	else
		vars->max = float_abs(xyz->y_step);
}

void	step_modification(t_xyz *xyz, t_vars *vars)
{
	xyz->x_step /= vars->max;
	xyz->y_step /= vars->max;
}

unsigned int	random_color(void)
{
	return ((unsigned int)(rand() % 0xFFFFFF) + 1);
}

unsigned int	generate_color_gradient(void)
{
	unsigned int	color;

	color = random_color();
	color += 0x000101;
	if (color > 0xFFFFFF)
		color = 0x000000;
	return (color);
}

void	final_drawing(t_xyz *xyz, t_vars *vars)
{
	while ((int)(xyz->x - xyz->x1) || (int)(xyz->y - xyz->y1))
	{
		mlx_pixel_put(vars->mlx, vars->win, (int) xyz->x,
			(int) xyz->y, vars->color);
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
		vars->color = 0x000000;
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
			vars->color = generate_color_gradient();
		else
			vars->color = 0xff00ff;
	}
}

void	bresenham(t_xyz xyz, t_vars *vars)
{
	init_z(&xyz, vars);
	zooming(&xyz, vars);
	isometric_two_coordinates(&xyz, vars->angle, vars);
	shifting(&xyz, vars);
	init_step(&xyz);
	init_max(&xyz, vars);
	step_modification(&xyz, vars);
	coloring(&xyz, vars);
	final_drawing(&xyz, vars);
}
