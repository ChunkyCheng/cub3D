/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collisions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:55:17 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 11:44:42 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

static int	is_player_map_collision(t_gamedata *gamedata, t_vect player_pos,
int map_x, int map_y)
{
	if (map_x < 0 || map_x >= MAP_SIZE_MAX
		|| map_y < 0 || map_y >= MAP_SIZE_MAX)
		return (0);
	if (gamedata->map[map_y][map_x].e_type == WALL
		&& is_collision(player_hitbox(player_pos), cell_hitbox(map_x, map_y)))
		return (1);
	return (0);
}

int	is_xy_collision(t_gamedata *gamedata, t_player *player,
t_vect move_dir)
{
	t_vect	new_pos;
	int		map_x;
	int		map_y;

	new_pos.x = player->pos.x + move_dir.x;
	new_pos.y = player->pos.y + move_dir.y;
	map_x = (int)player->pos.x + ft_get_sign(move_dir.x);
	map_y = (int)player->pos.y;
	if (is_player_map_collision(gamedata, new_pos, map_x, map_y - 1)
		|| is_player_map_collision(gamedata, new_pos, map_x, map_y)
		|| is_player_map_collision(gamedata, new_pos, map_x, map_y + 1))
		return (1);
	map_x = (int)player->pos.x;
	map_y += ft_get_sign(move_dir.y);
	if (is_player_map_collision(gamedata, new_pos, map_x - 1, map_y)
		|| is_player_map_collision(gamedata, new_pos, map_x, map_y)
		|| is_player_map_collision(gamedata, new_pos, map_x + 1, map_y))
		return (1);
	return (0);
}

int	is_x_collision(t_gamedata *gamedata, t_player *player,
t_vect move_dir)
{
	t_vect	new_pos;
	int		map_x;
	int		map_y;

	new_pos.x = player->pos.x + move_dir.x;
	new_pos.y = player->pos.y;
	map_x = (int)player->pos.x + ft_get_sign(move_dir.x);
	map_y = (int)player->pos.y - 1;
	while (map_y <= (int)player->pos.y + 1)
	{
		if (is_player_map_collision(gamedata, new_pos, map_x, map_y))
			return (1);
		map_y++;
	}
	return (0);
}

int	is_y_collision(t_gamedata *gamedata, t_player *player,
t_vect move_dir)
{
	t_vect	new_pos;
	int		map_x;
	int		map_y;

	new_pos.x = player->pos.x;
	new_pos.y = player->pos.y + move_dir.y;
	map_x = (int)player->pos.x - 1;
	map_y = (int)player->pos.y + ft_get_sign(move_dir.y);
	while (map_x <= (int)player->pos.x + 1)
	{
		if (is_player_map_collision(gamedata, new_pos, map_x, map_y))
			return (1);
		map_x++;
	}
	return (0);
}
