/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:52:21 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 18:07:13 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static int	is_out_of_bounds(t_ray *ray)
{
	if (ray->pos.y < 0 || ray->pos.y >= MAP_SIZE_MAX
		|| ray->pos.x < 0 || ray->pos.x >= MAP_SIZE_MAX)
	{
		ray->out_of_bounds = 1;
		return (1);
	}
	return (0);
}

void	cast_ray(t_gamedata *gamedata, t_ray *ray, t_player *player)
{
	while (1)
	{
		if (ray->side_dist.x < ray->side_dist.y || ray->e_type == HORIZONTAL)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->pos.x += ray->step.x;
			ray->e_side = X_SIDE;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->pos.y += ray->step.y;
			ray->e_side = Y_SIDE;
		}
		if (is_out_of_bounds(ray))
			return ;
		if (gamedata->map[(int)ray->pos.y][(int)ray->pos.x].e_type == WALL)
			break ;
	}
	if (ray->e_side == X_SIDE)
		ray->len = (ray->pos.x - player->pos.x + (1 - ray->step.x) / 2)
			/ ray->dir.x;
	else
		ray->len = (ray->pos.y - player->pos.y + (1 - ray->step.y) / 2)
			/ ray->dir.y;
}
