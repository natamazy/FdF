/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:25:54 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/20 12:25:25 by natamazy         ###   ########.fr       */
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
	vars->img->addr = mlx_get_data_addr(vars->img->img, &vars->img->bits_per_pixel, &vars->img->line_length,
								&(vars->img->endian));
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

int	key_hook(int keycode, t_vars *vars)
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
	else if (keycode == 31)
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
	else if (keycode == 17)
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
	if (keycode == 24 || keycode == 27 || keycode == 32 || keycode == 2 || keycode == 123 || keycode == 124 ||
		keycode == 125 || keycode == 126 || keycode == 31 || keycode == 35 || (keycode >= 17 && keycode <= 20) || keycode == 3)
		draw_new(vars);
	return (0);
}

void	init_standart(t_vars *vars, t_data *img)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "test");
	img->img = mlx_new_image(vars->mlx, 1920, 1080);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&(img->endian));
	vars->zoom = 10;
	vars->z_zoom = 0;
	vars->x_shift = 300;
	vars->y_shift = 300;
	vars->angle = 0.8;
	vars->img = img;
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
	mlx_loop(vars.mlx);
}
