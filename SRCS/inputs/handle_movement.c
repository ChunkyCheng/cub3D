/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:55:17 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/21 18:34:10 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

static float	get_move_dist(int move_flags)
{
	if ((move_flags == (W_HOLD | A_HOLD))
		|| (move_flags == (W_HOLD | D_HOLD))
		|| (move_flags == (S_HOLD | A_HOLD))
		|| (move_flags == (S_HOLD | D_HOLD)))
		return (MOVE_SPEED / M_SQRT2);
	return (MOVE_SPEED);
}

static t_vect	get_movement_vector(int move_flags, t_player *player)
{
	const float	move_dist = get_move_dist(move_flags);
	t_vect		move_dir;

	move_dir = (t_vect){0};
	if (move_flags & W_HOLD)
	{
		move_dir.x += player->dir.x * move_dist;
		move_dir.y += player->dir.y * move_dist;
	}
	if (move_flags & A_HOLD)
	{
		move_dir.x += player->dir.y * move_dist;
		move_dir.y -= player->dir.x * move_dist;
	}
	if (move_flags & S_HOLD)
	{
		move_dir.x -= player->dir.x * move_dist;
		move_dir.y -= player->dir.y * move_dist;
	}
	if (move_flags & D_HOLD)
	{
		move_dir.x -= player->dir.y * move_dist;
		move_dir.y += player->dir.x * move_dist;
	}
	return (move_dir);
}

static double	axis_post_collision(double axis_val, double move_dir)
{
	if (move_dir < 0)
		return ((int)axis_val + PLAYER_RADIUS);
	else
		return ((int)axis_val + 1 - PLAYER_RADIUS);
}

void	handle_movement(t_gamedata *gamedata,
t_inputs *inputs, t_player *player)
{
	t_vect	move_dir;
	t_vect	new_pos;

	move_dir = get_movement_vector(inputs->move_flags, player);
	if (move_dir.x == 0 && move_dir.y == 0)
		return ;
	new_pos.x = player->pos.x + move_dir.x;
	new_pos.y = player->pos.y + move_dir.y;
	if (is_xy_collision(gamedata, player, move_dir))
	{
		if (move_dir.x && is_x_collision(gamedata, player, move_dir))
			new_pos.x = axis_post_collision(player->pos.x, move_dir.x);
		if (move_dir.y && is_y_collision(gamedata, player, move_dir))
			new_pos.y = axis_post_collision(player->pos.y, move_dir.y);
		if (new_pos.x == player->pos.x + move_dir.x
			&& new_pos.y == player->pos.y + move_dir.y)
		{
			new_pos.x = axis_post_collision(player->pos.x, move_dir.x);
			new_pos.y = axis_post_collision(player->pos.y, move_dir.y);
		}
	}
	player->pos.x = ft_round_to(new_pos.x, QUANTIZE_STEP);
	player->pos.y = ft_round_to(new_pos.y, QUANTIZE_STEP);
}
