/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:33:49 by natamazy          #+#    #+#             */
/*   Updated: 2024/03/20 21:52:24 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../minilibx_macos/mlx.h"
#include <math.h>

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
