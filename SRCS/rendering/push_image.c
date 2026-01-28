/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:20:07 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 23:22:29 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	scale_image(t_image *main, t_image *buff,
t_upscaling *upscaling)
{
	int		main_x;
	int		main_y;
	int		buff_x;
	int		buff_y;
	int		pixel;

	main_y = 0;
	while (main_y < WIN_HEIGHT - upscaling->y_bound)
	{
		main_x = 0;
		buff_y = upscaling->scale_map_y[main_y];
		while (main_x < WIN_WIDTH - upscaling->x_bound)
		{
			buff_x = upscaling->scale_map_x[main_x];
			pixel = image_get_pixel(buff, buff_x, buff_y);
			image_put_pixel(main, main_x, main_y, pixel);
			main_x++;
		}
		main_y++;
	}
}

void	push_image(t_gamedata *gamedata)
{
	t_upscaling	*upscaling;

	upscaling = &gamedata->cache->upscaling;
	if (upscaling->needs_scaling)
	{
		scale_image(&gamedata->img_main, &gamedata->img_buff, upscaling);
		mlx_put_image_to_window(gamedata->display, gamedata->window,
			gamedata->img_main.mlx_img,
			upscaling->x_offset, upscaling->y_offset);
	}
	else
	{
		mlx_put_image_to_window(gamedata->display, gamedata->window,
			gamedata->img_buff.mlx_img,
			upscaling->x_offset, upscaling->y_offset);
	}
}
