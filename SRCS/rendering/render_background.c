/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 23:38:32 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/03 17:12:29 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	fill_remaining(t_image *img_buff, int y, int colour)
{
	int	x;

	while (y < IMG_HEIGHT / 2)
	{
		x = 0;
		while (x < IMG_WIDTH)
		{
			image_put_pixel(img_buff, x, y, colour);
			image_put_pixel(img_buff, x, IMG_HEIGHT - 1 - y, colour);
			x++;
		}
		y++;
	}
}

static void	fill_row(t_gamedata *gamedata, t_texture_pack *texture_pack,
int y, float darkness)
{
	int	ceiling;
	int	floor;
	int	x;

	ceiling = pixel_blend(gamedata->cache->fog_colour,
			texture_pack->ceiling, darkness);
	floor = pixel_blend(gamedata->cache->fog_colour,
			texture_pack->floor, darkness);
	x = 0;
	while (x < IMG_WIDTH)
	{
		image_put_pixel(&gamedata->img_buff, x, y, ceiling);
		image_put_pixel(&gamedata->img_buff, x, IMG_HEIGHT - 1 - y, floor);
		x++;
	}
}

void	render_background(t_gamedata *gamedata,
t_texture_pack *texture_pack, t_cache *cache)
{
	int		y;
	int		y_limit;
	float	darkness;

	y = 0;
	y_limit = (IMG_HEIGHT - cache->min_wall_height) / 2;
	while (y < y_limit)
	{
		darkness = (2.0 / (cache->min_wall_height - IMG_HEIGHT))
			* y + 1.0;
		fill_row(gamedata, texture_pack, y, darkness);
		y++;
	}
	fill_remaining(&gamedata->img_buff, y, cache->fog_colour);
}
