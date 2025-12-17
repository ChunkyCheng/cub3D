/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:20:07 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/17 12:25:36 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	render_background(t_image *img_buff, t_texture_pack *texture_pack)
{
	int	x;
	int	y;

	y = 0;
	while (y < IMG_HEIGHT / 2)
	{
		x = 0;
		while (x < IMG_WIDTH)
		{
			image_put_pixel(img_buff, x, y, texture_pack->ceiling);
			x++;
		}
		y++;
	}
	while (y < IMG_HEIGHT)
	{
		x = 0;
		while (x < IMG_WIDTH)
		{
			image_put_pixel(img_buff, x, y, texture_pack->floor);
			x++;
		}
		y++;
	}
}

static void	scale_image(t_image *main, t_image *buff,
t_render_vals *render_vals)
{
	int		main_x;
	int		main_y;
	int		buff_x;
	int		buff_y;
	int		pixel;

	main_y = 0;
	while (main_y < WIN_HEIGHT - render_vals->y_bound)
	{
		main_x = 0;
		buff_y = render_vals->scale_map_y[main_y];
		while (main_x < WIN_WIDTH - render_vals->x_bound)
		{
			buff_x = render_vals->scale_map_x[main_x];
			pixel = image_get_pixel(buff, buff_x, buff_y);
			image_put_pixel(main, main_x, main_y, pixel);
			main_x++;
		}
		main_y++;
	}
}

//Formula for view_plane_len = tan(fov / 2) where fov is in radians
//Thus final formula is tan(fov * pi / 360)
void	render_frame(t_gamedata *gamedata, t_player *player)
{
	t_ray	ray;
	int		col;

	render_background(&gamedata->img_buff, &gamedata->texture_pack);
	player->view_plane_len = tan(120 * M_PI / 360);
	player->projection_dist = IMG_WIDTH / 2 / player->view_plane_len;
	player->view_plane.x = -player->dir.y * player->view_plane_len;
	player->view_plane.y = player->dir.x * player->view_plane_len;
	col = 0;
	while (col < IMG_WIDTH)
	{
		init_ray(&ray, player, col);
		cast_ray(gamedata, &ray, player);
		if (!ray.out_of_bounds)
			render_column(gamedata, &ray, col);
		col++;
	}
	scale_image(&gamedata->img_main, &gamedata->img_buff,
		gamedata->render_vals);
	mlx_put_image_to_window(gamedata->display, gamedata->window,
		gamedata->img_main.mlx_img,
		gamedata->render_vals->x_offset, gamedata->render_vals->y_offset);
	limit_framerate();
}
