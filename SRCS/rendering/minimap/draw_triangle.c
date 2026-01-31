/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_triangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:40:56 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/31 21:52:54 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"
#include "minimap.h"

static void	sort_points(t_triangle *triangle)
{
	t_int_vect	temp;

	if (triangle->p0.y > triangle->p1.y)
	{
		temp = triangle->p0;
		triangle->p0 = triangle->p1;
		triangle->p1 = temp;
	}
	if (triangle->p1.y > triangle->p2.y)
	{
		temp = triangle->p1;
		triangle->p1 = triangle->p2;
		triangle->p2 = temp;
	}
	if (triangle->p0.y > triangle->p1.y)
	{
		temp = triangle->p0;
		triangle->p0 = triangle->p1;
		triangle->p1 = temp;
	}
}

static void	draw_scanline(t_image *dst, t_line_x *line)
{
	int	i;
	int	temp;

	if (line->x_start > line->x_end)
	{
		temp = line->x_start;
		line->x_start = line->x_end;
		line->x_end = temp;
	}
	i = line->x_start;
	while (i <= line->x_end)
	{
		image_put_pixel(dst, i, line->y, line->colour);
		i++;
	}
}

static void	draw_flat_bottom(t_image *dst, t_triangle *triangle)
{
	int			x_left_fp;
	int			x_right_fp;
	int			dx_left_fp;
	int			dx_right_fp;
	t_line_x	line;

	if (triangle->p0.y == triangle->p2.y)
		return ;
	x_left_fp = triangle->p0.x << 16;
	x_right_fp = x_left_fp;
	dx_left_fp = ((triangle->p1.x - triangle->p0.x) << 16)
		/ (triangle->p1.y - triangle->p0.y);
	dx_right_fp = ((triangle->p2.x - triangle->p0.x) << 16)
		/ (triangle->p2.y - triangle->p0.y);
	line.y = triangle->p0.y;
	line.colour = triangle->colour;
	while (line.y <= triangle->p1.y)
	{
		line.x_start = (x_left_fp - 0x8000) >> 16;
		line.x_end = (x_right_fp - 0x8000) >> 16;
		draw_scanline(dst, &line);
		x_left_fp += dx_left_fp;
		x_right_fp += dx_right_fp;
		line.y++;
	}
}

static void	draw_flat_top(t_image *dst, t_triangle *triangle)
{
	int			x_left_fp;
	int			x_right_fp;
	int			dx_left_fp;
	int			dx_right_fp;
	t_line_x	line;

	if (triangle->p0.y == triangle->p2.y)
		return ;
	x_left_fp = triangle->p0.x << 16;
	x_right_fp = triangle->p1.x << 16;
	dx_left_fp = ((triangle->p2.x - triangle->p0.x) << 16)
		/ (triangle->p2.y - triangle->p0.y);
	dx_right_fp = ((triangle->p2.x - triangle->p1.x) << 16)
		/ (triangle->p2.y - triangle->p1.y);
	line.y = triangle->p0.y;
	line.colour = triangle->colour;
	while (line.y <= triangle->p2.y)
	{
		line.x_start = (x_left_fp - 0x8000) >> 16;
		line.x_end = (x_right_fp - 0x8000) >> 16;
		draw_scanline(dst, &line);
		x_left_fp += dx_left_fp;
		x_right_fp += dx_right_fp;
		line.y++;
	}
}

void	draw_triangle(t_image *dst, t_triangle *triangle)
{
	t_triangle	flat_bottom;
	t_triangle	flat_top;
	t_int_vect	p0p2_cut_point;

	sort_points(triangle);
	if (triangle->p1.y == triangle->p2.y)
		draw_flat_bottom(dst, triangle);
	else if (triangle->p0.y == triangle->p1.y)
		draw_flat_top(dst, triangle);
	else
	{
		p0p2_cut_point.y = triangle->p1.y;
		p0p2_cut_point.x
			= triangle->p0.x + (p0p2_cut_point.y - triangle->p0.y)
			* (float)(triangle->p0.x - triangle->p2.x)
			/ (triangle->p0.y - triangle->p2.y);
		flat_bottom = *triangle;
		flat_bottom.p2 = p0p2_cut_point;
		flat_top = *triangle;
		flat_top.p0 = p0p2_cut_point;
		draw_flat_bottom(dst, &flat_bottom);
		draw_flat_top(dst, &flat_top);
	}
}
