/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:55:17 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 11:45:37 by lming-ha         ###   ########.fr       */
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

static void	set_movement_vector(t_vect *move_dir,
int move_flags, t_player *player)
{
	double	move_dist;

	move_dist = get_move_dist(move_flags);
	*move_dir = (t_vect){0};
	if (move_flags & W_HOLD)
	{
		move_dir->x += player->dir.x * move_dist;
		move_dir->y += player->dir.y * move_dist;
	}
	if (move_flags & A_HOLD)
	{
		move_dir->x += player->dir.y * move_dist;
		move_dir->y -= player->dir.x * move_dist;
	}
	if (move_flags & S_HOLD)
	{
		move_dir->x -= player->dir.x * move_dist;
		move_dir->y -= player->dir.y * move_dist;
	}
	if (move_flags & D_HOLD)
	{
		move_dir->x -= player->dir.y * move_dist;
		move_dir->y += player->dir.x * move_dist;
	}
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

	set_movement_vector(&move_dir, inputs->move_flags, player);
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
	player->pos.x = ft_decimal_round(new_pos.x, 3);
	player->pos.y = ft_decimal_round(new_pos.y, 3);
}
