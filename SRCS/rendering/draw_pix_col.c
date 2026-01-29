/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pix_col.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 21:23:36 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/29 23:08:38 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

void	draw_pix_col(t_image *dst, t_pix_col *pix_col, float darkness)
{
	int	i;
	int	tex_y_fp;
	int	tex_step_fp;
	int	screen_y;
	int	pixel;

	i = 0;
	tex_y_fp = pix_col->tex_y_top * (1 << 16);
	tex_step_fp = pix_col->tex_step * (1 << 16);
	screen_y = pix_col->screen_y_top;
	while (i < pix_col->draw_height)
	{
		pixel = image_get_pixel(pix_col->texture,
				pix_col->tex_x, tex_y_fp >> 16);
		if ((pixel & ALPHA) != ALPHA)
		{
			pixel = darken_pixel(pixel, darkness);
			image_put_pixel(dst, pix_col->screen_x, screen_y, pixel);
		}
		screen_y++;
		tex_y_fp += tex_step_fp;
		i++;
	}
}
