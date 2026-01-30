/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:33:35 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 11:45:37 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static double	get_ray_hit_pos(t_ray *ray, t_player *player)
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

static void	set_pixel_col_texture(t_map_cell *cell_hit, t_ray *ray,
t_pixel_col *pixel_col)
{
	if (ray->e_side == Y_SIDE && ray->dir.y > 0)
		pixel_col->texture = cell_hit->north;
	else if (ray->e_side == Y_SIDE)
		pixel_col->texture = cell_hit->south;
	else if (ray->dir.x > 0)
		pixel_col->texture = cell_hit->west;
	else
		pixel_col->texture = cell_hit->east;
}

static void	init_pixel_col(t_gamedata *gamedata, t_ray *ray,
t_pixel_col *pixel_col)
{
	double	ray_hit_pos;

	set_pixel_col_texture(&gamedata->map[ray->norm_y][ray->norm_x],
		ray, pixel_col);
	ray_hit_pos = get_ray_hit_pos(ray, &gamedata->player);
	pixel_col->len = gamedata->render_vals->projection_dist / ray->len;
	if ((ray->e_side == Y_SIDE && ray->dir.y < 0)
		|| (ray->e_side == X_SIDE && ray->dir.x > 0))
		pixel_col->col = (int)(pixel_col->texture->width * ray_hit_pos);
	else
		pixel_col->col = (int)(pixel_col->texture->width * (1 - ray_hit_pos));
	pixel_col->row_step = pixel_col->texture->height / pixel_col->len;
	if (pixel_col->len > IMG_HEIGHT)
		pixel_col->row = (pixel_col->len - IMG_HEIGHT) / 2
			* pixel_col->row_step;
	else
		pixel_col->row = 0;
}

void	render_column(t_gamedata *gamedata, t_ray *ray, int screen_col)
{
	t_pixel_col	pixel_col;
	int			screen_row;
	int			pixel;
	int			i;
	float		darkness;

	init_pixel_col(gamedata, ray, &pixel_col);
	if (pixel_col.len > IMG_HEIGHT)
		screen_row = 0;
	else
		screen_row = round((IMG_HEIGHT - pixel_col.len) / 2);
	darkness = (2.0 / (gamedata->render_vals->min_wall_height - IMG_HEIGHT))
		* screen_row + 1.0;
	i = 0;
	while (screen_row < (IMG_HEIGHT + pixel_col.len) / 2
		&& screen_row < IMG_HEIGHT)
	{
		pixel = image_get_pixel(pixel_col.texture,
				pixel_col.col, (int)(pixel_col.row + i * pixel_col.row_step));
		pixel = darken_pixel(pixel, darkness);
		image_put_pixel(&gamedata->img_buff, screen_col, screen_row, pixel);
		i++;
		screen_row++;
	}
}
