/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:32:57 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/30 16:42:09 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_edge_flood(t_map *map, int **mask, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (mask[y][x] != 0)
		return (0);
	mask[y][x] = 3;
	if (map->content[y][x] != ' ')
		return (1);
	if (check_edge_flood(map, mask, x + 1, y))
		return (1);
	if (check_edge_flood(map, mask, x - 1, y))
		return (1);
	if (check_edge_flood(map, mask, x, y + 1))
		return (1);
	if (check_edge_flood(map, mask, x, y - 1))
		return (1);
	return (0);
}

static void	spread_walls(t_map *map, int **mask, int x, int y)
{
	int	dx;
	int	dy;
	int	nx;
	int	ny;

	if (ret_wall(map->content[y][x]))
		mask[y][x] = 2;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			nx = x + dx;
			ny = y + dy;
			if (nx >= 0 && nx < map->width && ny >= 0 && ny < map->height
				&& !mask[ny][nx] && ret_wall(map->content[ny][nx]))
			{
				mask[ny][nx] = 2;
				spread_walls(map, mask, nx, ny);
			}
			dx++;
		}
		dy++;
	}
}

void	flood_fill(t_map *map, int **mask, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return ;
	if (mask[y][x])
		return ;
	mask[y][x] = 1;
	if (ret_wall(map->content[y][x]))
		return (spread_walls(map, mask, x, y));
	flood_fill(map, mask, x + 1, y);
	flood_fill(map, mask, x - 1, y);
	flood_fill(map, mask, x, y + 1);
	flood_fill(map, mask, x, y - 1);
}
