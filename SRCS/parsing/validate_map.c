/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:00:00 by lming-ha          #+#    #+#             */
/*   Updated: 2026/04/01 04:15:36 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_filled(t_map *map)
{
	int	x;
	int	y;

	printf("\033[33m+");
	x = -1;
	while (++x < map->width)
		printf("-");
	printf("+\033[0m\n");
	y = -1;
	while (++y < map->height)
	{
		printf("\033[33m|\033[0m");
		x = -1;
		while (++x < map->width)
		{
			if (map->mask[y][x] == 1)
			{
				if (map->content[y][x] == ' ')
					printf("\033[44m \033[0m");
				else
					printf("\033[44;30m%c\033[0m", map->content[y][x]);
			}
			else if (map->mask[y][x] == 2)
			{
				if (map->content[y][x] == ' ')
					printf("\033[41m \033[0m");
				else
					printf("\033[41;30m%c\033[0m", map->content[y][x]);
			}
			else
				printf("%c", map->content[y][x]);
		}
		printf("\033[33m|\033[0m\n");
	}
	printf("\033[33m+");
	x = -1;
	while (++x < map->width)
		printf("-");
	printf("+\033[0m\n");
}

static void	check_void(t_map *map, t_parsing *p_data, t_gamedata *gamedata)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (map->mask[x][y] != 1 && map->content[x][y] != ' ')
				clean_error(p_data, gamedata, "Map is not enclosed");
			if (map->content[x][y] == 'C')
				add_coin(gamedata, p_data, y, x);
			y++;
		}
		x++;
	}
}

static void	flood_fill(t_map *map, int **mask, int x, int y)
{
	static const int	dir4[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	static const int	dir8[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
		{1, 0}, {-1, 1}, {0, 1}, {1, 1}};
	int					i;

	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return ;
	if (map->mode == 0)
	{
		if (mask[y][x] == 2 || get_wall(map->content[y][x]))
			return ;
		mask[y][x] = 2;
		i = -1;
		while (++i < 4)
			flood_fill(map, mask, x + dir4[i][0], y + dir4[i][1]);
		return ;
	}
	if (mask[y][x])
		return ;
	mask[y][x] = 1;
	i = -1;
	while (++i < 8)
	{
		if ((i == 0 || i == 2 || i == 5 || i == 7)
			&& (x + dir8[i][0] < 0 || x + dir8[i][0] >= map->width
			|| y + dir8[i][1] < 0 || y + dir8[i][1] >= map->height))
			continue ;
		flood_fill(map, mask, x + dir8[i][0], y + dir8[i][1]);
	}
}

static void	flood_void(t_map *map, int **mask)
{
	int	i;

	i = -1;
	while (++i < map->width)
	{
		flood_fill(map, mask, i, 0);
		flood_fill(map, mask, i, map->height - 1);
	}
	i = -1;
	while (++i < map->height)
	{
		flood_fill(map, mask, 0, i);
		flood_fill(map, mask, map->width - 1, i);
	}
}

static int	**create_map_mask(int height, int width)
{
	int	**mask;
	int	y;

	mask = ft_calloc(height, sizeof(int *));
	if (!mask)
		return (NULL);
	y = 0;
	while (y < height)
	{
		mask[y] = ft_calloc(width, sizeof(int));
		if (!mask[y])
		{
			while (--y >= 0)
				free(mask[y]);
			free(mask);
			return (NULL);
		}
		y++;
	}
	return (mask);
}

void	validate_map(t_gamedata *gamedata, t_parsing *p_data)
{
	int	x;
	int	y;

	p_data->map.mask = create_map_mask(p_data->map.height, p_data->map.width);
	if (!p_data->map.mask)
		clean_error(p_data, gamedata, "Allocation failure");
	flood_void(&p_data->map, p_data->map.mask);
	x = (int)gamedata->player.pos.x;
	y = (int)gamedata->player.pos.y;
	if (DEBUG)
		print_filled(&p_data->map);
	if (p_data->map.mask[y][x] == 2)
		clean_error(p_data, gamedata, "Map is not enclosed");
	p_data->map.mode = 1;
	flood_fill(&p_data->map, p_data->map.mask, x, y);
	check_void(&p_data->map, p_data, gamedata);
	if (DEBUG)
		print_filled(&p_data->map);
}
