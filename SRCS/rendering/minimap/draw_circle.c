/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:18:14 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 21:03:15 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "minimap.h"
#include "rendering.h"

static void	draw_init_points(t_image *dst, t_circle *circle)
{
	image_put_pixel(dst, 0 + circle->mid_x, circle->radius + circle->mid_y,
		circle->colour);
	image_put_pixel(dst, 0 + circle->mid_x, -circle->radius + circle->mid_y,
		circle->colour);
	image_put_pixel(dst, circle->radius + circle->mid_x, 0 + circle->mid_y,
		circle->colour);
	image_put_pixel(dst, -circle->radius + circle->mid_x, 0 + circle->mid_y,
		circle->colour);
}

static void	draw_octants(t_image *dst, int x, int y, t_circle *circle)
{
	image_put_pixel(dst, x + circle->mid_x, y + circle->mid_y,
		circle->colour);
	image_put_pixel(dst, x + circle->mid_x, -y + circle->mid_y,
		circle->colour);
	image_put_pixel(dst, -x + circle->mid_x, y + circle->mid_y,
		circle->colour);
	image_put_pixel(dst, -x + circle->mid_x, -y + circle->mid_y,
		circle->colour);
	if (x != y)
	{
		image_put_pixel(dst, y + circle->mid_x, x + circle->mid_y,
			circle->colour);
		image_put_pixel(dst, y + circle->mid_x, -x + circle->mid_y,
			circle->colour);
		image_put_pixel(dst, -y + circle->mid_x, x + circle->mid_y,
			circle->colour);
		image_put_pixel(dst, -y + circle->mid_x, -x + circle->mid_y,
			circle->colour);
	}
}

void	draw_circle(t_image *dst, t_circle *circle)
{
	int	x;
	int	y;
	int	p;

	draw_init_points(dst, circle);
	x = circle->radius;
	y = 0;
	p = 1 - circle->radius;
	while (x > y)
	{
		y++;
		if (p <= 0)
			p += (2 * y) + 1;
		else
		{
			x--;
			p += (2 * y) - (2 * x) + 1;
		}
		if (x < y)
			break ;
		draw_octants(dst, x, y, circle);
	}
}
