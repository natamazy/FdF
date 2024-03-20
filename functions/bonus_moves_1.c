/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_moves_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:46:21 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/20 21:49:52 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"
#include <math.h>

void	isometric(float *x, float *y, int z, t_vars *vars)
{
	if (vars->flip == 1)
	{
		*x = (*x + *y) * cos(vars->angle);
		*y = (*x - *y) * sin(vars->angle) - z;
	}
	else
	{
		*x = (*x - *y) * cos(vars->angle);
		*y = (*x + *y) * sin(vars->angle) - z;
	}
}

void	isometric_two_coordinates(t_xyz *xyz, t_vars *vars)
{
	if (vars->top_view == 1)
		return ;
	isometric(&(xyz->x), &(xyz->y), xyz->z1, vars);
	isometric(&(xyz->x1), &(xyz->y1), xyz->z2, vars);
}

float	float_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	shifting(t_xyz *xyz, t_vars *vars)
{
	xyz->x += vars->x_shift;
	xyz->y += vars->y_shift;
	xyz->x1 += vars->x_shift;
	xyz->y1 += vars->y_shift;
}

void	zooming(t_xyz *xyz, t_vars *vars)
{
	xyz->x *= vars->zoom;
	xyz->y *= vars->zoom;
	xyz->x1 *= vars->zoom;
	xyz->y1 *= vars->zoom;
}
