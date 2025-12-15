/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:22:53 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 18:08:55 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	render_background(t_image *img_main, t_texture_pack *texture_pack)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			image_put_pixel(img_main, x, y, texture_pack->ceiling);
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			image_put_pixel(img_main, x, y, texture_pack->floor);
			x++;
		}
		y++;
	}
}

//Formula for view_plane_len = tan(fov / 2) where fov is in radians
//Thus final formula is tan(fov * pi / 360)
void	render_frame(t_gamedata *gamedata, t_player *player)
{
	t_ray	ray;
	int		col;

	render_background(&gamedata->img_main, &gamedata->texture_pack);
	player->view_plane_len = tan(player->fov * M_PI / 360);
	player->projection_dist = WIN_WIDTH / 2 / player->view_plane_len;
	player->view_plane.x = -player->dir.y * player->view_plane_len;
	player->view_plane.y = player->dir.x * player->view_plane_len;
	col = 0;
	while (col < WIN_WIDTH)
	{
		init_ray(&ray, player, col);
		cast_ray(gamedata, &ray, player);
		if (!ray.out_of_bounds)
			render_column(gamedata, &ray, col);
		col++;
	}
	mlx_put_image_to_window(gamedata->display, gamedata->window,
		gamedata->img_main.mlx_img, 0, 0);
}
