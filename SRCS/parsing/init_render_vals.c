/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render_vals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:53:30 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/30 19:33:09 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

//for rendering. Do not change in parsing but use in parsing
static void	calculate_upscale_map(t_render_vals *render_vals)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		render_vals->scale_map_x[i] = round(i * render_vals->scale);
		i++;
	}
	i = 0;
	while (i < WIN_HEIGHT)
	{
		render_vals->scale_map_y[i] = round(i * render_vals->scale);
		i++;
	}
}

void	init_render_vals(t_render_vals *render_vals)
{
	if (WIN_HEIGHT < WIN_WIDTH)
	{
		render_vals->scale = (IMG_HEIGHT - 1) / (WIN_HEIGHT - 1.0);
		render_vals->x_bound = WIN_WIDTH
			- floor(IMG_WIDTH / render_vals->scale) + 1;
		render_vals->y_bound = 0;
		render_vals->x_offset = render_vals->x_bound / 2;
		render_vals->y_offset = 0;
	}
	else
	{
		render_vals->scale = (IMG_WIDTH - 1) / (WIN_WIDTH - 1.0);
		render_vals->x_bound = 0;
		render_vals->y_bound = WIN_HEIGHT
			- floor(IMG_HEIGHT / render_vals->scale) + 1;
		render_vals->x_offset = 0;
		render_vals->y_offset = render_vals->y_bound / 2;
	}
	calculate_upscale_map(render_vals);
	render_vals->view_plane_len = tan(120 * M_PI / 360);
	render_vals->projection_dist = IMG_WIDTH / 2 / render_vals->view_plane_len;
}
