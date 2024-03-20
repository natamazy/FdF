/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:25:54 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/20 21:43:32 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"

#include <stdio.h>

void	draw_new(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_clear_window(vars->mlx, vars->win);
	vars->img->img = mlx_new_image(vars->mlx, 1920, 1080);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bits_per_pixel,
			&vars->img->line_length, &(vars->img->endian));
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

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
	return (0);
}

void	init_standart(t_vars *vars, t_data *img)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "test");
	img->img = mlx_new_image(vars->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &(img->endian));
	vars->zoom = 10;
	vars->z_zoom = 0;
	vars->x_shift = 300;
	vars->y_shift = 300;
	vars->angle = 0.8;
	vars->img = img;
}

int	exit_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
}

int	main(int argc, char *argv[])
{
	t_vars	vars;
	t_data	img;

	if (validation(argc, argv, &vars) == 1)
		return (1);
	init_standart(&vars, &img);
	draw(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_window, &vars);
	mlx_loop(vars.mlx);
}
