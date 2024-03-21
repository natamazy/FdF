/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:25:54 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/21 13:09:54 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"

#include <stdio.h>

void	init_standart(t_vars *vars, t_data *img)
{
	vars->length = 1920;
	vars->width = 1080;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->length,
			vars->width, "natamazy / FdF");
	img->img = mlx_new_image(vars->mlx, vars->length, vars->width);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &(img->endian));
	vars->zoom = 10;
	vars->z_zoom = 0;
	vars->x_shift = 800;
	vars->y_shift = 400;
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
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, exit_window, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
