/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:33:49 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/18 13:42:23 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"

#include <math.h>

void	isometric(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void	bresenham(float x, float y, float x1, float y1, t_vars *vars)
{
	float	x_step;
	float	y_step;
	int		max;
	float	modul_xstep;
	float	modul_ystep;
	int		color;

	int	z1 = vars->map[(int)y][(int)x];
	int	z2 = vars->map[(int)y1][(int)x1];

	if (z1 > 0 || z2 > 0)
		color = 0xff0000;
	else
		color = 0xffffff;

	x *= vars->zoom;
	y *= vars->zoom;
	x1 *= vars->zoom;
	y1 *= vars->zoom;

	x_step = x1 - x;
	y_step = y1 - y;
	
	if (x_step < 0)
		modul_xstep = -x_step;
	else
		modul_xstep = x_step;
	if (y_step < 0)
		modul_ystep = -y_step;
	else
		modul_ystep = y_step;
	
	// isometric(&x, &y, z1);
	// isometric(&x1, &y1, z2);
	if (x_step > y_step)
		max = x_step;
	else
		max = y_step;
	
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
