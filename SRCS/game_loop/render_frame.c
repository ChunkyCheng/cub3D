/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:22:53 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/13 18:22:26 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

void	cast_ray(t_gamedata *gamedata, t_ray *ray, int col)
{


}

void render_frame(t_gamedata *gamedata, t_player *player)
{
	t_ray	ray;
	int		col;
	float	view_plane_pos;

	player->view_plane_len = tan(player->fov / 2);
	player->view_plane.x = -player->dir.y * player->view_plane_len;
	player->view_plane.y = player->dir.x * player->view_plane_len;
	ray.pos.x = player->pos.x;
	ray.pos.y = player->pos.y;
	col = 0;
	while (col < WIN_WIDTH)
	{
		view_plane_pos = 2.0 * col / (WIN_WIDTH - 1.0) - 1;
		ray.dir.x = player->dir.x + player->view_plane.x * view_plane_pos;
		ray.dir.y = player->dir.y + player->view_plane.y * view_plane_pos;
		cast_ray(gamedata, &ray, col);
		col++;
	}
	mlx_put_image_to_window(gamedata->display, gamedata->window,
		gamedata->img_main.mlx_img, 0, 0);
}
