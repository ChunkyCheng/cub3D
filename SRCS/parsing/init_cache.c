/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render_vals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:53:30 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 22:57:11 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

//for rendering. Do not change in parsing but use in parsing
static void	calculate_upscale_map(t_cache *cache)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		cache->scale_map_x[i] = round(i * cache->scale);
		i++;
	}
	i = 0;
	while (i < WIN_HEIGHT)
	{
		cache->scale_map_y[i] = round(i * cache->scale);
		i++;
	}
}

void	init_cache(t_cache *cache)
{
	if (WIN_HEIGHT < WIN_WIDTH)
	{
		cache->scale = (IMG_HEIGHT - 1) / (WIN_HEIGHT - 1.0);
		cache->x_bound = WIN_WIDTH
			- floor(IMG_WIDTH / cache->scale) + 1;
		cache->y_bound = 0;
		cache->x_offset = cache->x_bound / 2;
		cache->y_offset = 0;
	}
	else
	{
		cache->scale = (IMG_WIDTH - 1) / (WIN_WIDTH - 1.0);
		cache->x_bound = 0;
		cache->y_bound = WIN_HEIGHT
			- floor(IMG_HEIGHT / cache->scale) + 1;
		cache->x_offset = 0;
		cache->y_offset = cache->y_bound / 2;
	}
	calculate_upscale_map(cache);
	cache->view_plane_len = tan(DFL_FOV * M_PI / 360);
	cache->projection_dist = IMG_WIDTH / 2 / cache->view_plane_len;
	cache->min_wall_height
		= round(cache->projection_dist / DFL_VIEW_DIST);
}
