/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:40:28 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 23:40:52 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"

void	init_minimap(t_gamedata *gamedata, t_minimap *minimap)
{
	(void)gamedata;
	if (IMG_HEIGHT <= IMG_WIDTH)
		minimap->pix_size = IMG_HEIGHT * MINIMAP_SIZE;
	else
		minimap->pix_size = IMG_WIDTH * MINIMAP_SIZE;
	minimap->wall_size
		= ceil(minimap->pix_size / MINIMAP_MAP_RADIUS);
	minimap->screen_x = minimap->pix_size / 2 + IMG_WIDTH * 0.05;
	minimap->screen_y = minimap->pix_size / 2 + IMG_WIDTH * 0.05;
	minimap->outline.radius = minimap->pix_size;
	minimap->outline.mid_x = minimap->screen_x;
	minimap->outline.mid_y = minimap->screen_y;
	minimap->outline.colour = 0xFFFFFF;
}
