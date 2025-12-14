/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:22:53 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/14 16:21:50 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

void	render_frame(t_gamedata *gamedata, t_player *player)
{
	t_ray	ray;
	int		col;

	player->view_plane_len = tan(player->fov / 2);
	player->view_plane.x = -player->dir.y * player->view_plane_len;
	player->view_plane.y = player->dir.x * player->view_plane_len;
	col = 0;
	while (col < WIN_WIDTH)
	{
		init_ray(&ray, player, col);
		cast_ray(gamedata, &ray, player);
		col++;
	}
	mlx_put_image_to_window(gamedata->display, gamedata->window,
		gamedata->img_main.mlx_img, 0, 0);
}
