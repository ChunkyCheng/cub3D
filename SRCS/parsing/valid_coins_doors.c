/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_coins_doors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:23:36 by lming-ha          #+#    #+#             */
/*   Updated: 2026/02/04 18:26:16 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_wall(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	return (get_wall(map->content[y][x]));
}

static int	check_door_valid(t_map *map, int x, int y)
{
	int	d[4];

	d[2] = 0;
	d[3] = 0;
	d[1] = -2;
	while (++d[1] <= 1)
	{
		d[0] = -2;
		while (++d[0] <= 1)
		{
			if (!(d[0] || d[1]))
				continue ;
			if (is_wall(map, x + d[0], y + d[1]))
				d[3]++;
			else if (x + d[0] >= 0 && x + d[0] < map->width
				&& y + d[1] >= 0 && y + d[1] < map->height
				&& map->content[y + d[1]][x + d[0]] == 'D')
				d[2]++;
		}
	}
	return (!((d[2] == 0 && d[3] < 2) || (d[2] == 1 && d[3] < 1)));
}

static void	flood_fill_doors(t_map *map, int x, int y, int *valid)
{
	int	d[2];

	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return ;
	if ((map->mask[y][x] & 4) || map->content[y][x] != 'D')
		return ;
	map->mask[y][x] |= 4;
	if (!check_door_valid(map, x, y))
		*valid = 0;
	d[1] = -2;
	while (++d[1] <= 1)
	{
		d[0] = -2;
		while (++d[0] <= 1)
			if ((d[0] || d[1]) && x + d[0] >= 0 && x + d[0] < map->width
				&& y + d[1] >= 0 && y + d[1] < map->height
				&& map->content[y + d[1]][x + d[0]] == 'D')
				flood_fill_doors(map, x + d[0], y + d[1], valid);
	}
}

void	valid_coins_doors(t_map *map, t_parsing *p_data, t_gamedata *gamedata)
{
	int		x;
	int		y;
	int		valid;

	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (map->content[y][x] == 'D' && !(map->mask[y][x] & 4))
			{
				valid = 1;
				flood_fill_doors(map, x, y, &valid);
				if (!valid)
					clean_error(p_data, gamedata, "Invalid door placement");
			}
			if (map->content[y][x] == 'C')
				add_coin(gamedata, p_data, x, y);
		}
	}
}
