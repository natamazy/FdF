/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:33:49 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/21 13:08:38 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"
#include <math.h>

void	draw_new(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_clear_window(vars->mlx, vars->win);
	vars->img->img = mlx_new_image(vars->mlx, vars->length, vars->width);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&vars->img->bits_per_pixel,
			&vars->img->line_length, &(vars->img->endian));
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
}

void	bresenham(t_xyz xyz, t_vars *vars)
{
	init_z(&xyz, vars);
	zooming(&xyz, vars);
	isometric_two_coordinates(&xyz, vars);
	shifting(&xyz, vars);
	init_step(&xyz);
	init_max(&xyz, vars);
	step_modification(&xyz, vars);
	coloring(&xyz, vars);
	final_drawing(&xyz, vars);
}
