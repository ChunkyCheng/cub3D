/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:20:07 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/29 15:19:27 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	image_duplicate_row(t_image *image, int row_dst, int row_src)
{
	void	*dst;
	void	*src;

	dst = image->pixels + row_dst * image->row_len;
	src = image->pixels + row_src * image->row_len;
	ft_memcpy(dst, src, image->row_len);
}

static int	scale_row(t_image *main, t_image *buff,
t_upscaling *upscaling, int main_y)
{
	int	main_x;
	int	buff_x;
	int	buff_y;
	int	pixel;

	main_x = 0;
	buff_y = upscaling->scale_map_y[main_y];
	while (main_x < WIN_WIDTH - upscaling->x_bound)
	{
		buff_x = upscaling->scale_map_x[main_x];
		pixel = image_get_pixel(buff, buff_x, buff_y);
		image_put_pixel(main, main_x, main_y, pixel);
		main_x++;
	}
	return (buff_y);
}

static void	scale_image(t_image *main, t_image *buff,
t_upscaling *upscaling)
{
	int	main_y;
	int	buff_y;

	main_y = 0;
	while (main_y < WIN_HEIGHT - upscaling->y_bound)
	{
		if (main_y > 0
			&& upscaling->scale_map_y[main_y] == buff_y)
			image_duplicate_row(main, main_y, main_y - 1);
		else
			buff_y = scale_row(main, buff, upscaling, main_y);
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
