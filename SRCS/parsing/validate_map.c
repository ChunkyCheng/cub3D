/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:00:00 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/30 16:41:26 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	free_intarr(int **arr, int height)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < height)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	check_disconnected(t_map *map, int **mask)
{
	int	x;
	int	y;
	int	result;

	result = 0;
	y = -1;
	while (++y < map->height && !result)
	{
		if (mask[y][0] == 0)
			result = check_edge_flood(map, mask, 0, y);
		if (!result && mask[y][map->width - 1] == 0)
			result = check_edge_flood(map, mask, map->width - 1, y);
	}
	x = -1;
	while (++x < map->width && !result)
	{
		if (mask[0][x] == 0)
			result = check_edge_flood(map, mask, x, 0);
		if (!result && mask[map->height - 1][x] == 0)
			result = check_edge_flood(map, mask, x, map->height - 1);
	}
	return (result);
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
	int	**mask;
	int	x;
	int	y;

	mask = create_map_mask(p_data->map.height, p_data->map.width);
	if (!mask)
		clean_error(p_data, gamedata, "Allocation failure");
	x = (int)gamedata->player.pos.x;
	y = (int)gamedata->player.pos.y;
	flood_fill(&p_data->map, mask, x, y);
	if (check_disconnected(&p_data->map, mask))
	{
		free_intarr(mask, p_data->map.height);
		clean_error(p_data, gamedata, "Map is not closed/surrounded by walls");
	}
	free_intarr(mask, p_data->map.height);
}
