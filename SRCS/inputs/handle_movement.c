/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:55:17 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/18 00:11:33 by jchuah           ###   ########.fr       */
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

static int	is_x_collision(t_gamedata *gamedata, t_player *player,
t_vect move_dir)
{
	t_vect	new_pos;
	int		x;
	int		y;

	new_pos.x = player->pos.x + move_dir.x;
	new_pos.y = player->pos.y;
	if (move_dir.x < 0)
		x = (int)player->pos.x - 1;
	else
		x = (int)player->pos.x + 1;
	y = (int)player->pos.y;
	if (y >= 0 && y < MAP_SIZE_MAX)
	{
		if (gamedata->map[y][x].e_type == WALL)
		{
			if (is_collision(player_hitbox(new_pos), cell_hitbox(x, y)))
				return (1);
		}
	}
	return (0);
}

static int	is_y_collision(t_gamedata *gamedata, t_player *player,
t_vect move_dir)
{
	t_vect	new_pos;
	int		x;
	int		y;

	new_pos.x = player->pos.x;
	new_pos.y = player->pos.y + move_dir.y;
	if (move_dir.y < 0)
		y = (int)player->pos.y - 1;
	else
		y = (int)player->pos.y + 1;
	x = (int)player->pos.x;
	if (x >= 0 && x < MAP_SIZE_MAX)
	{
		if (gamedata->map[y][x].e_type == WALL)
		{
			if (is_collision(player_hitbox(new_pos), cell_hitbox(x, y)))
				return (1);
		}
	}
	return (0);
}

void	handle_movement(t_gamedata *gamedata,
t_inputs *inputs, t_player *player)
{
	const t_vect	move_dir = get_movement_vector(inputs->move_flags, player);
	t_vect			new_pos;

	if (move_dir.x == 0 && move_dir.y == 0)
		return ;
	if (is_x_collision(gamedata, player, move_dir))
	{
		if (move_dir.x < 0)
			new_pos.x = ((int)player->pos.x + PLAYER_RADIUS);
		else
			new_pos.x = ((int)player->pos.x + 1 - PLAYER_RADIUS);
	}
	else
		new_pos.x = player->pos.x + move_dir.x;
	if (is_y_collision(gamedata, player, move_dir))
	{
		if (move_dir.y < 0)
			new_pos.y = (int)player->pos.y + PLAYER_RADIUS;
		else
			new_pos.y = (int)player->pos.y + 1 - PLAYER_RADIUS;
	}
	else
		new_pos.y = player->pos.y + move_dir.y;
	player->pos.x = new_pos.x;
	player->pos.y = new_pos.y;
}
