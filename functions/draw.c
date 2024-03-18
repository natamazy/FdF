/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:33:49 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/18 19:12:39 by natamazy         ###   ########.fr       */
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

float	float_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	bresenham(float x, float y, float x1, float y1, t_vars *vars)
{
	float	x_step;
	float	y_step;
	int		max;
	int		color;

	int	z1 = vars->map[(int)y][(int)x];
	int	z2 = vars->map[(int)y1][(int)x1];

	if (z1 > 0)
		z1 += vars->z_zoom;
	if (z2 > 0)
		z2 += vars->z_zoom;
	if (z1 > 0 || z2 > 0)
		color = 0xff0000;
	else
		color = 0xffffff;
	x *= vars->zoom;
	y *= vars->zoom;
	x1 *= vars->zoom;
	y1 *= vars->zoom;
	isometric(&x, &y, z1, vars->angle);
	isometric(&x1, &y1, z2, vars->angle);
	x += vars->shift;
	y += vars->shift;
	x1 += vars->shift;
	y1 += vars->shift;
	
	x_step = x1 - x;
	y_step = y1 - y;
	
	if (float_abs(x_step) > float_abs(y_step))
		max = float_abs(x_step);
	else
		max = float_abs(y_step);
	
	x_step /= max;
	y_step /= max;

	while ((int) (x - x1) || (int) (y - y1))
	{
		mlx_pixel_put(vars->mlx, vars->win, (int) x, (int) y, color);
		x += x_step;
		y += y_step;
	}
}

void	draw(t_vars *vars)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < vars->y_size)
	{
		x = 0;
		while (x < vars->x_size)
		{
			if (x < vars->x_size - 1)
				bresenham(x, y, x + 1, y, vars);
			if (y < vars->y_size - 1)
				bresenham(x, y, x, y + 1, vars);
			x++;
		}
		y++;
	}
}
