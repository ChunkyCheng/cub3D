/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 20:59:11 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/31 00:35:30 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"
#include "minimap.h"

void	draw_rectangle(t_image *dst, t_rectangle *rectangle)
{
	int		x;
	int		y;
	void	*pixel_dst;
	void	*pixel_src;
	int		width;

	x = rectangle->top_x;
	y = rectangle->top_y;
	while (x < rectangle->bot_x)
	{
		image_put_pixel(dst, x, y, rectangle->colour);
		x++;
	}
	pixel_src = dst->pixels + y * dst->row_len + rectangle->top_x * sizeof(int);
	pixel_dst = pixel_src + dst->row_len;
	width = rectangle->bot_x - rectangle->top_x;
	y++;
	while (y < rectangle->bot_y && y < dst->height)
	{
		ft_memcpy(pixel_dst, pixel_src, width * sizeof(int));
		pixel_dst += dst->row_len;
		y++;
	}
}
