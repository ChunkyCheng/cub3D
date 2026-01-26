/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_use_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:11:07 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/26 17:37:39 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

static t_map_cell	*get_facing_door(t_gamedata *gamedata, t_player *player)
{
	int	x;
	int	y;

	x = (int)(player->pos.x + player->dir.x * REACH_DIST);
	y = (int)(player->pos.y + player->dir.y * REACH_DIST);
	if (gamedata->map[y][x].e_type == DOOR)
	{
		if (!is_collision(player_hitbox(player->pos), cell_hitbox(x, y)))
			return (&gamedata->map[y][x]);
	}
	return (NULL);
}

void	handle_use_key(t_gamedata *gamedata, t_inputs *inputs, t_player *player)
{
	static int	use_hold;
	t_map_cell	*door;

	if ((inputs->move_flags & E_HOLD) && (!use_hold))
	{
		use_hold = 1;
		door = get_facing_door(gamedata, player);
		if (!door)
			return ;
		door->solid = !door->solid;
		door->visible = door->solid;
	}
	if (!(inputs->move_flags & E_HOLD))
		use_hold = 0;
}
