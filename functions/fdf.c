/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:25:54 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/18 19:17:18 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"

#include <stdio.h>

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 69)
		vars->zoom += 1;
	else if (keycode == 78)
		vars->zoom -= 1;
	else if (keycode == 32)
		vars->z_zoom += 5;
	else if (keycode == 2)
		vars->z_zoom -= 5;
	else if (keycode == 126)
		vars->angle -= 0.01;
	else if (keycode == 125)
		vars->angle += 0.01;
	mlx_clear_window(vars->mlx, vars->win);
	draw(vars);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (validation(argc, argv, &vars) == 1)
		return (1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000, "test");
	vars.zoom = 30;
	vars.z_zoom = 0;
	vars.shift = 150;
	vars.angle = 0.8;
	draw(&vars);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_loop(vars.mlx);
}
