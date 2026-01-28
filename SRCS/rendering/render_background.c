/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 23:38:32 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 22:58:58 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	fill_remaining(t_image *img_buff, int y)
{
	int	x;

	while (y < IMG_HEIGHT / 2)
	{
		x = 0;
		while (x < IMG_WIDTH)
		{
			image_put_pixel(img_buff, x, y, BLACK);
			image_put_pixel(img_buff, x, IMG_HEIGHT - 1 - y, BLACK);
			x++;
		}
		y++;
	}
}

void	render_background(t_image *img_buff, t_texture_pack *texture_pack,
t_cache *cache, t_player *player)
{
	int		x;
	int		y;
	int		y_limit;
	float	darkness;

	(void)player;
	y = 0;
	y_limit = (IMG_HEIGHT - cache->min_wall_height) / 2;
	while (y < y_limit)
	{
		darkness = (2.0 / (cache->min_wall_height - IMG_HEIGHT))
			* y + 1.0;
		x = 0;
		while (x < IMG_WIDTH)
		{
			image_put_pixel(img_buff, x, y,
				darken_pixel(texture_pack->ceiling, darkness));
			image_put_pixel(img_buff, x, IMG_HEIGHT - 1 - y,
				darken_pixel(texture_pack->floor, darkness));
			x++;
		}
		y++;
	}
	fill_remaining(img_buff, y);
}
