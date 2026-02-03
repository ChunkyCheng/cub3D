/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_column.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:33:35 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/03 22:06:42 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static float	get_ray_hit_pos(t_ray *ray, t_player *player)
{
	double	hit_pos;

	if (ray->e_type == VERTICAL)
		hit_pos = player->pos.x;
	else if (ray->e_type == HORIZONTAL)
		hit_pos = player->pos.y;
	else if (ray->e_side == X_SIDE)
		hit_pos = player->pos.y + ray->len * ray->dir.y;
	else
		hit_pos = player->pos.x + ray->len * ray->dir.x;
	hit_pos = hit_pos - (int)hit_pos;
	return (hit_pos);
}

static void	set_pix_col_texture(t_map_cell *cell_hit, t_ray *ray,
t_pix_col *pix_col)
{
	if (ray->e_side == Y_SIDE && ray->dir.y > 0)
		pix_col->texture = cell_hit->north;
	else if (ray->e_side == Y_SIDE)
		pix_col->texture = cell_hit->south;
	else if (ray->dir.x > 0)
		pix_col->texture = cell_hit->west;
	else
		pix_col->texture = cell_hit->east;
}

void	render_wall_column(t_gamedata *gamedata, t_ray *ray, int screen_col)
{
	float		ray_hit_pos;
	t_pix_col	pix_col;
	float		darkness;

	set_pix_col_texture(&gamedata->map[ray->norm_y][ray->norm_x],
		ray, &pix_col);
	pix_col.full_height = gamedata->cache->projection_dist / ray->len;
	ray_hit_pos = get_ray_hit_pos(ray, &gamedata->player);
	pix_col.tex_x = pix_col.texture->width * ray_hit_pos;
	if ((ray->e_side == Y_SIDE && ray->dir.y > 0)
		|| (ray->e_side == X_SIDE && ray->dir.x < 0))
		pix_col.tex_x = pix_col.texture->width - 1 - pix_col.tex_x;
	pix_col.screen_x = screen_col;
	init_pix_col(&pix_col);
	darkness = (2.0 / (gamedata->cache->min_wall_height - IMG_HEIGHT))
		* pix_col.screen_y_top + 1.0;
	draw_pix_col(&gamedata->img_buff, &pix_col,
		gamedata->cache->fog_colour, darkness);
	gamedata->cache->z_buffer[screen_col] = ray->len;
}
