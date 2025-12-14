/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:22:53 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/14 16:21:21 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	init_ray_pos_and_dir(t_ray *ray, t_player *player, int col)
{
	float	view_plane_pos;

	ray->pos.x = (int)player->pos.x;
	ray->pos.y = (int)player->pos.y;
	view_plane_pos = 2.0 * col / (WIN_WIDTH - 1.0) - 1;
	ray->dir.x = player->dir.x + player->view_plane.x * view_plane_pos;
	ray->dir.y = player->dir.y + player->view_plane.y * view_plane_pos;
}

static void	init_ray_deltas(t_ray *ray)
{
	ray->e_type = ANGLED;
	if (ray->dir.x)
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	else
		ray->e_type = VERTICAL;
	if (ray->dir.y)
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	else
		ray->e_type = HORIZONTAL;
}

static void	init_ray_steps(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (player->pos.x - ray->pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->pos.x + 1 - player->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (player->pos.y - ray->pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->pos.y + 1 - player->pos.y) * ray->delta_dist.y;
	}
}

void	init_ray(t_ray *ray, t_player *player, int col)
{
	*ray = (t_ray){0};
	init_ray_pos_and_dir(ray, player, col);
	init_ray_deltas(ray);
	init_ray_steps(ray, player);
}
