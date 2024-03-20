/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_moves_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:47:11 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/20 21:57:51 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"
#include <math.h>

void	init_z(t_xyz *xyz, t_vars *vars)
{
	xyz->z1 = vars->map[(int)xyz->y][(int)xyz->x];
	xyz->z2 = vars->map[(int)xyz->y1][(int)xyz->x1];
	if (xyz->z1 != 0)
		xyz->z1 += vars->z_zoom;
	if (xyz->z2 != 0)
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

int	random_color(void)
{
	return ((unsigned int)(rand() % 0xFFFFFF) + 1);
}
