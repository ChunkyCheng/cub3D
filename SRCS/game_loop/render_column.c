/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_column.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:33:35 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 18:47:45 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

float	get_ray_hit_pos(t_ray *ray, t_player *player)
{
	float	hit_pos;

	if (ray->e_type == VERTICAL)
		hit_pos = player->pos.x;
	else if (ray->e_type == HORIZONTAL)
		hit_pos = player->pos.y;
	else if (ray->e_side == X_SIDE)
		hit_pos = player->pos.y + ray->len * ray->dir.y;
	else
		hit_pos = player->pos.x + ray->len * ray->dir.x;
	hit_pos = hit_pos - floor(hit_pos);
	return (hit_pos);
}

static void	init_pixel_col(t_gamedata *gamedata, t_ray *ray,
t_pixel_col *pixel_col)
{
	float		ray_hit_pos;
	t_texture	*texture;

	ray_hit_pos = get_ray_hit_pos(ray, &gamedata->player);
	texture = gamedata->map[(int)ray->pos.y][(int)ray->pos.x].texture;
	if (ray->e_side == Y_SIDE && ray->dir.y > 0)
		pixel_col->texture = &texture->north;
	else if (ray->e_side == Y_SIDE)
		pixel_col->texture = &texture->south;
	else if (ray->dir.x > 0)
		pixel_col->texture = &texture->west;
	else
		pixel_col->texture = &texture->east;
	pixel_col->len = round(gamedata->player.projection_dist / ray->len);
	if ((ray->e_side == Y_SIDE && ray->dir.y < 0)
		|| (ray->e_side == X_SIDE && ray->dir.x > 0))
		pixel_col->col = round(pixel_col->texture->width * ray_hit_pos);
	else
		pixel_col->col = round(pixel_col->texture->width * (1 - ray_hit_pos));
	pixel_col->row_step = pixel_col->texture->height / (float)pixel_col->len;
	if (pixel_col->len > WIN_HEIGHT)
		pixel_col->row = (pixel_col->len - WIN_HEIGHT) / 2
			* pixel_col->row_step;
	else
		pixel_col->row = 0;
}

void	render_column(t_gamedata *gamedata, t_ray *ray, int screen_col)
{
	t_pixel_col	pixel_col;
	int			screen_row;
	int			pixel;

	init_pixel_col(gamedata, ray, &pixel_col);
	if (pixel_col.len > WIN_HEIGHT)
		screen_row = 0;
	else
		screen_row = (WIN_HEIGHT - pixel_col.len) / 2;
	while (screen_row < (WIN_HEIGHT + pixel_col.len) / 2
		&& screen_row < WIN_HEIGHT)
	{
		pixel = image_get_pixel(pixel_col.texture,
				pixel_col.col, round(pixel_col.row));
		image_put_pixel(&gamedata->img_main, screen_col, screen_row, pixel);
		screen_row++;
		pixel_col.row += pixel_col.row_step;
	}
}
