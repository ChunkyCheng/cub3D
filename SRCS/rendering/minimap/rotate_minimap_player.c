/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_minimap_player.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 19:12:48 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/01 00:30:07 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"
#include "minimap.h"

static void	rotate_point(t_int_vect *point, int (*rot_matrix_fp)[2][2])
{
	int	new_x_fp;
	int	new_y_fp;

	new_x_fp = (*rot_matrix_fp)[0][0] * point->x
		+ (*rot_matrix_fp)[0][1] * point->y;
	new_y_fp = (*rot_matrix_fp)[1][0] * point->x
		+ (*rot_matrix_fp)[1][1] * point->y;
	point->x = new_x_fp >> 16;
	point->y = new_y_fp >> 16;
}

static void	translate_triangle(t_triangle *triangle, int x, int y)
{
	triangle->p0.x += x;
	triangle->p1.x += x;
	triangle->p2.x += x;
	triangle->p0.y += y;
	triangle->p1.y += y;
	triangle->p2.y += y;
}

t_triangle	rotate_minimap_player(t_minimap *minimap, t_player *player)
{
	int			rot_matrix_fp[2][2];
	t_triangle	new_triangle;

	rot_matrix_fp[0][0] = -player->dir.y * (1 << 16);
	rot_matrix_fp[0][1] = -player->dir.x * (1 << 16);
	rot_matrix_fp[1][0] = player->dir.x * (1 << 16);
	rot_matrix_fp[1][1] = -player->dir.y * (1 << 16);
	new_triangle = minimap->player;
	translate_triangle(&new_triangle, -minimap->screen_x, -minimap->screen_y);
	rotate_point(&new_triangle.p0, &rot_matrix_fp);
	rotate_point(&new_triangle.p1, &rot_matrix_fp);
	rotate_point(&new_triangle.p2, &rot_matrix_fp);
	translate_triangle(&new_triangle, minimap->screen_x, minimap->screen_y);
	return (new_triangle);
}
