/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:52:21 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/29 22:15:42 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static int	is_out_of_bounds(t_ray *ray, t_player *player)
{
	if (ray->norm_y < 0 || ray->norm_y >= MAP_SIZE_MAX
		|| ray->norm_x < 0 || ray->norm_x >= MAP_SIZE_MAX
		|| ray->len > player->view_dist)
	{
		ray->out_of_bounds = 1;
		return (1);
	}
	return (0);
}

static void	set_perpendicular_distance(t_ray *ray, t_player *player)
{
	if (ray->e_side == X_SIDE)
		ray->len = (ray->norm_x - player->pos.x + (1.0 - ray->step.x) / 2)
			/ ray->dir.x;
	else
		ray->len = (ray->norm_y - player->pos.y + (1.0 - ray->step.y) / 2)
			/ ray->dir.y;
}

void	cast_ray(t_gamedata *gamedata, t_ray *ray, t_player *player)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y || ray->e_type == HORIZONTAL)
		{
			ray->len = ray->side_dist.x;
			ray->side_dist.x += ray->delta_dist.x;
			ray->norm_x += ray->step.x;
			ray->e_side = X_SIDE;
		}
		else
		{
			ray->len = ray->side_dist.y;
			ray->side_dist.y += ray->delta_dist.y;
			ray->norm_y += ray->step.y;
			ray->e_side = Y_SIDE;
		}
		if (is_out_of_bounds(ray, player))
			return ;
		if (gamedata->map[ray->norm_y][ray->norm_x].visible)
			break ;
	}
	set_perpendicular_distance(ray, player);
}
