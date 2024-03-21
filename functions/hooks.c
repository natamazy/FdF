/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:06:17 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/21 15:07:55 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 24 || keycode == 27 || keycode == 32
		|| keycode == 2 || (keycode >= 123 && keycode <= 126))
		bonus_part_1(keycode, vars);
	else if (keycode == 31 || keycode == 35
		|| (keycode >= 18 && keycode <= 20))
		bonus_part_2(keycode, vars);
	else if (keycode == 17 || keycode == 3)
		bonus_part_3(keycode, vars);
	if (keycode == 24 || keycode == 27 || keycode == 32
		|| keycode == 2 || (keycode >= 123 && keycode <= 126) || keycode == 31
		|| keycode == 35 || (keycode >= 17 && keycode <= 20) || keycode == 3)
		draw_new(vars);
	if (keycode == 53)
		exit_window(vars);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	if (x && y)
		;
	if (keycode == 5)
		vars->zoom += 1;
	else if (keycode == 4)
		vars->zoom -= 1;
	if (keycode == 5 || keycode == 4)
		draw_new(vars);
	return (0);
}

int	exit_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
}
