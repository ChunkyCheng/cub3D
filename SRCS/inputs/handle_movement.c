/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:55:17 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 17:24:40 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

static float	get_move_dist(t_inputs *inputs)
{
	if ((inputs->move_flags == (W_HOLD | A_HOLD))
		|| (inputs->move_flags == (W_HOLD | D_HOLD))
		|| (inputs->move_flags == (S_HOLD | A_HOLD))
		|| (inputs->move_flags == (S_HOLD | D_HOLD)))
		return (MOVE_SPEED / sqrt(2));
	return (MOVE_SPEED);
}

void	handle_movement(t_inputs *inputs, t_player *player)
{
	const float	move_dist = get_move_dist(inputs);

	if (inputs->move_flags & W_HOLD)
	{
		player->pos.x += player->dir.x * move_dist;
		player->pos.y += player->dir.y * move_dist;
	}
	if (inputs->move_flags & A_HOLD)
	{
		player->pos.x += player->dir.y * move_dist;
		player->pos.y -= player->dir.x * move_dist;
	}
	if (inputs->move_flags & S_HOLD)
	{
		player->pos.x -= player->dir.x * move_dist;
		player->pos.y -= player->dir.y * move_dist;
	}
	if (inputs->move_flags & D_HOLD)
	{
		player->pos.x -= player->dir.y * move_dist;
		player->pos.y += player->dir.x * move_dist;
	}
}
