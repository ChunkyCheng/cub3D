/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:20:07 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/29 22:02:04 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

//Formula for view_plane_len = tan(fov / 2) where fov is in radians
//Thus final formula is tan(fov * pi / 360)
void	render_frame(t_gamedata *gamedata, t_cache *cache,
t_player *player)
{
	t_ray	ray;
	int		col;

	render_background(&gamedata->img_buff, &gamedata->texture_pack,
		gamedata->cache, &gamedata->player);
	player->view_plane.x = -player->dir.y * cache->view_plane_len;
	player->view_plane.y = player->dir.x * cache->view_plane_len;
	col = 0;
	while (col < IMG_WIDTH)
	{
		init_ray(&ray, player, col);
		cast_ray(gamedata, &ray, player);
		if (!ray.out_of_bounds)
			render_wall_column(gamedata, &ray, col);
		col++;
	}
	render_coins(gamedata, &gamedata->player, &gamedata->coins);
	push_image(gamedata);
	limit_framerate();
}
