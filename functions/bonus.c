/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:39:54 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/20 21:40:26 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	bonus_part_1(int keycode, t_vars *vars)
{
	if (keycode == 24)
		vars->zoom += 1;
	else if (keycode == 27)
		vars->zoom -= 1;
	else if (keycode == 32)
		vars->z_zoom += 10;
	else if (keycode == 2)
		vars->z_zoom -= 10;
	else if (keycode == 124)
		vars->x_shift += 10;
	else if (keycode == 123)
		vars->x_shift -= 10;
	else if (keycode == 125)
		vars->y_shift += 10;
	else if (keycode == 126)
		vars->y_shift -= 10;
}

void	bonus_part_2(int keycode, t_vars *vars)
{
	if (keycode == 31)
		vars->angle += 0.1;
	else if (keycode == 35)
		vars->angle -= 0.1;
	else if (keycode >= 18 && keycode <= 20)
	{
		if (keycode == 18)
			vars->color_mode = 1;
		else if (keycode == 19)
			vars->color_mode = 2;
		else
			vars->color_mode = 3;
	}
}

void	bonus_part_3(int keycode, t_vars *vars)
{
	if (keycode == 17)
	{
		if (vars->top_view == 1)
			vars->top_view = 0;
		else
			vars->top_view = 1;
	}
	else if (keycode == 3)
	{
		if (vars->flip == 1)
			vars->flip = 0;
		else
			vars->flip = 1;
	}
}
