/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:20:07 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/26 17:32:30 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

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
void	render_frame(t_gamedata *gamedata, t_render_vals *render_vals,
t_player *player)
{
	t_ray	ray;
	int		col;

	render_background(&gamedata->img_buff, &gamedata->texture_pack,
		gamedata->render_vals, &gamedata->player);
	player->view_plane.x = -player->dir.y * render_vals->view_plane_len;
	player->view_plane.y = player->dir.x * render_vals->view_plane_len;
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
		render_vals->x_offset, render_vals->y_offset);
	limit_framerate();
}
