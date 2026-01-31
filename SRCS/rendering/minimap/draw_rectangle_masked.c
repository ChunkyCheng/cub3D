/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle_masked.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 14:29:00 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/31 15:33:23 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"
#include "minimap.h"

static void	draw_scanline(t_image *dst, t_rectangle *rect, t_circle *mask,
int y)
{
	int	x_min;
	int	x_max;
	int	mask_x;

	mask_x = round(sqrt(mask->radius * mask->radius
				- (y - mask->mid_y) * (y - mask ->mid_y)));
	if (mask->mid_x - mask_x >= rect->top_x)
		x_min = mask->mid_x - mask_x + 1;
	else
		x_min = rect->top_x;
	if (mask->mid_x + mask_x <= rect->bot_x)
		x_max = mask->mid_x + mask_x;
	else
		x_max = rect->bot_x;
	while (x_min < x_max)
	{
		image_put_pixel(dst, x_min, y, rect->colour);
		x_min++;
	}
}

void	draw_rectangle_masked(t_image *dst, t_rectangle *rect, t_circle *mask)
{
	int	y_min;
	int	y_max;

	if (mask->mid_y - mask->radius >= rect->top_y)
		y_min = mask->mid_y - mask->radius + 1;
	else
		y_min = rect->top_y;
	if (mask->mid_y + mask->radius <= rect->bot_y)
		y_max = mask->mid_y + mask->radius;
	else
		y_max = rect->bot_y;
	while (y_min < y_max)
	{
		draw_scanline(dst, rect, mask, y_min);
		y_min++;
	}
}
