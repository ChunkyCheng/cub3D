/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:49:15 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/30 09:42:06 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"
#include "parsing.h"
#include "rendering.h"

static void	init_player(t_gamedata *gamedata, int x, int y, char direction)
{
	gamedata->player.pos.x = x + 0.5;
	gamedata->player.pos.y = y + 0.5;
	if (direction == 'N')
	{
		gamedata->player.dir.y = -1;
		gamedata->player.angle = 270;
	}
	else if (direction == 'S')
	{
		gamedata->player.dir.y = 1;
		gamedata->player.angle = 90;
	}
	else if (direction == 'E')
	{
		gamedata->player.dir.x = 1;
		gamedata->player.angle = 0;
	}
	else
	{
		gamedata->player.dir.x = -1;
		gamedata->player.angle = 180;
	}
	gamedata->player.fov = DFL_FOV;
	gamedata->player.view_dist = DFL_VIEW_DIST;
}

void	parse_player(t_gamedata *gamedata, t_parsing *p_data)
{
	int	x;
	int	y;
	int	found;

	found = 0;
	y = -1;
	while (++y < p_data->map.height)
	{
		x = -1;
		while (p_data->map.content[y][++x])
		{
			if (ft_strchr("NSEW", p_data->map.content[y][x]))
			{
				if (found)
					clean_error(p_data, gamedata, "Multiple player positions");
				if (x == 0 || y == 0 || y == p_data->map.height - 1
					|| !p_data->map.content[y][x + 1])
					clean_error(p_data, gamedata, "Player on border");
				init_player(gamedata, x, y, p_data->map.content[y][x]);
				found = 1;
			}
		}
	}
	if (!found)
		clean_error(p_data, gamedata, "No player position found");
}
