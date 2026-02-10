/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:40:28 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/10 14:47:59 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"
#include "minimap.h"

static void	init_map_player(t_minimap *minimap, t_triangle *player,
		t_gamedata *gamedata)
{
	int	tip_dist;
	int	base_dist;
	int	base_len;

	tip_dist = minimap->wall_size * PLAYER_RADIUS * 3;
	base_dist = minimap->wall_size * PLAYER_RADIUS * 1.5;
	base_len = minimap->wall_size * PLAYER_RADIUS * 1.8;
	player->p0.x = minimap->screen_x;
	player->p0.y = minimap->screen_y - tip_dist;
	player->p1.x = minimap->screen_x - base_len;
	player->p1.y = minimap->screen_y + base_dist;
	player->p2.x = minimap->screen_x + base_len;
	player->p2.y = player->p1.y;
	player->colour = gamedata->texture_pack.floor ^ 0xFFFFFF;
}

void	init_minimap(t_gamedata *gamedata, t_minimap *minimap)
{
	int	smaller_axis;

	if (IMG_HEIGHT < IMG_WIDTH)
		smaller_axis = IMG_HEIGHT;
	else
		smaller_axis = IMG_WIDTH;
	minimap->pix_size = smaller_axis * MINIMAP_SIZE;
	minimap->wall_size
		= ceil(minimap->pix_size / (MINIMAP_MAP_RADIUS - 0.5));
	minimap->screen_x = minimap->pix_size + smaller_axis * 0.01;
	minimap->screen_y = minimap->pix_size + smaller_axis * 0.01;
	minimap->outline.radius = minimap->pix_size;
	minimap->outline.mid_x = minimap->screen_x;
	minimap->outline.mid_y = minimap->screen_y;
	minimap->outline.colour = 0xFFFFFF;
	minimap->visible = 0;
	init_map_player(minimap, &minimap->player, gamedata);
}
