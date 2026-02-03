/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_coins_doors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:23:36 by lming-ha          #+#    #+#             */
/*   Updated: 2026/02/03 15:40:29 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_door_chain(t_map *map, int x, int y, int direction)
{
	int	nx;
	int	ny;

	nx = x;
	ny = y;
	while (nx >= 0 && nx < map->width && ny >= 0 && ny < map->height)
	{
		if (map->content[ny][nx] != 'D')
			return (get_wall(map->content[ny][nx]));
		if (direction == 0)
			ny--;
		else if (direction == 1)
			ny++;
		else if (direction == 2)
			nx--;
		else if (direction == 3)
			nx++;
	}
	return (0);
}

static int	connected_door(t_map *map, int x, int y)
{
	int	top;
	int	bottom;
	int	left;
	int	right;

	top = check_door_chain(map, x, y - 1, 0);
	bottom = check_door_chain(map, x, y + 1, 1);
	left = check_door_chain(map, x - 1, y, 2);
	right = check_door_chain(map, x + 1, y, 3);
	if ((top && bottom) || (left && right))
		return (1);
	return (0);
}

void	valid_coins_doors(t_map *map, t_parsing *p_data, t_gamedata *gamedata)
{
	int		x;
	int		y;
	int		coins;

	y = 0;
	coins = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->content[y][x] == 'D')
			{
				if (!connected_door(map, x, y))
					clean_error(p_data, gamedata, "Invalid door placement");
			}
			if (map->content[y][x] == 'C')
				coins++;
			x++;
		}
		y++;
	}
	if (coins > COIN_MAX)
		clean_error(p_data, gamedata, "Too many coins");
}
