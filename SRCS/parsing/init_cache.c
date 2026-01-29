/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cache.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:53:30 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/29 15:11:24 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

//for rendering. Do not change in parsing but use in parsing

static void	init_upscaling(t_upscaling *upscaling)
{
	if (WIN_HEIGHT < WIN_WIDTH)
	{
		upscaling->scale = (IMG_HEIGHT - 1) / (WIN_HEIGHT - 1.0);
		upscaling->x_bound = WIN_WIDTH
			- floor(IMG_WIDTH / upscaling->scale) + 1;
		upscaling->y_bound = 0;
		upscaling->x_offset = upscaling->x_bound / 2;
		upscaling->y_offset = 0;
	}
	else
	{
		upscaling->scale = (IMG_WIDTH - 1) / (WIN_WIDTH - 1.0);
		upscaling->x_bound = 0;
		upscaling->y_bound = WIN_HEIGHT
			- floor(IMG_HEIGHT / upscaling->scale) + 1;
		upscaling->x_offset = 0;
		upscaling->y_offset = upscaling->y_bound / 2;
	}
}

static void	calculate_upscale_map(t_upscaling *upscaling)
{
	int	i;

	if ((IMG_WIDTH == WIN_WIDTH && IMG_HEIGHT <= WIN_HEIGHT)
		|| (IMG_HEIGHT == WIN_HEIGHT && IMG_WIDTH <= WIN_WIDTH))
	{
		upscaling->needs_scaling = 0;
		upscaling->x_offset = (WIN_WIDTH - IMG_WIDTH) / 2;
		upscaling->y_offset = (WIN_HEIGHT - IMG_HEIGHT) / 2;
		return ;
	}
	init_upscaling(upscaling);
	upscaling->needs_scaling = 1;
	i = 0;
	while (i < WIN_WIDTH)
	{
		upscaling->scale_map_x[i] = round(i * upscaling->scale);
		i++;
	}
	i = 0;
	while (i < WIN_HEIGHT)
	{
		upscaling->scale_map_y[i] = round(i * upscaling->scale);
		i++;
	}
}

void	init_cache(t_cache *cache)
{
	calculate_upscale_map(&cache->upscaling);
	cache->view_plane_len = tan(DFL_FOV * M_PI / 360);
	cache->projection_dist = IMG_WIDTH / 2 / cache->view_plane_len;
	cache->min_wall_height
		= round(cache->projection_dist / DFL_VIEW_DIST);
}
