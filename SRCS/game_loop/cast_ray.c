/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 19:52:21 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/13 20:25:42 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

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
			ray->pos.y += ray->pos.y;
			ray->e_side = Y_SIDE;
		}
		if (gamedata->map[(int)ray->pos.y][(int)ray->pos.x].e_type == WALL)
			break ;
	}
	if (ray->e_side == X_SIDE)
		ray->len = (ray->pos.x - player->pos.x + (1 - ray->step.x) / 2)
			/ ray->dir.x;
	else
		ray->len = (ray->pos.y - player->pos.y + (1 - ray->step.y) / 2)
			/ ray->dir.y;
	if (ray->e_side == X_SIDE)
		printf("ray hit x side at (%f, %f), distance of %f",
				ray->pos.x, ray->pos.y, ray->len);
	else
		printf("ray hit y side at (%f, %f), distance of %f",
				ray->pos.x, ray->pos.y, ray->len);
}
