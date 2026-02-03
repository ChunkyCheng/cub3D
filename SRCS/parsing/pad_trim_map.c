/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_trim_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 08:36:58 by lming-ha          #+#    #+#             */
/*   Updated: 2026/02/03 15:35:01 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	row_empty(char *row, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (row[i] != ' ' && row[i] != '\n' && row[i] != '\0')
			return (0);
		i++;
	}
	return (1);
}

static int	col_empty(t_map *map, int col)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		if (map->content[y][col] != ' ')
			return (0);
		y++;
	}
	return (1);
}

static int	find_bounds(t_map *map, int *bound, const int og_width)
{
	bound[0] = 0;
	bound[1] = map->height - 1;
	bound[2] = 0;
	bound[3] = og_width - 1;
	while (bound[0] <= bound[1] && row_empty(map->content[bound[0]], og_width))
		bound[0]++;
	while (bound[1] > bound[0] && row_empty(map->content[bound[1]], og_width))
		bound[1]--;
	while (bound[2] <= bound[3] && col_empty(map, bound[2]))
		bound[2]++;
	while (bound[3] > bound[2] && col_empty(map, bound[3]))
		bound[3]--;
	if (bound[0] > bound[1] || bound[2] > bound[3])
	{
		ft_putendl_fd("Error\nMap contains only spaces", 2);
		return (0);
	}
	map->height = bound[1] - bound[0] + 1;
	map->width = bound[3] - bound[2] + 1;
	if (map->width > MAP_SIZE_MAX || map->height > MAP_SIZE_MAX)
	{
		ft_putendl_fd("Error\nMap exceeds maximum allowed size", 2);
		return (0);
	}
	return (1);
}

void	trim_map(t_map *map, t_parsing *p_data, t_gamedata *gamedata)
{
	int		bound[4];
	int		y;
	char	**new;

	if (!find_bounds(map, bound, map->width))
		clean_error(p_data, gamedata, NULL);
	new = malloc(sizeof(char *) * (bound[1] - bound[0] + 2));
	if (!new)
		clean_error(p_data, gamedata, "malloc failure");
	y = 0;
	while (bound[0] + y <= bound[1])
	{
		new[y] = ft_substr(map->content[bound[0] + y], bound[2], map->width);
		if (!new[y])
		{
			ft_strarr_free(new);
			clean_error(p_data, gamedata, "ft_substr failure");
		}
		y++;
	}
	new[y] = NULL;
	ft_strarr_free(map->content);
	map->content = new;
}

void	pad_map(t_map *map, t_parsing *p_data, t_gamedata *gamedata)
{
	int		y;
	int		len;
	char	*padded;

	y = 0;
	while (y < map->height)
	{
		len = ft_strlen(map->content[y]);
		if (len < map->width)
		{
			padded = ft_calloc(map->width + 1, 1);
			if (!padded)
				clean_error(p_data, gamedata, "ft_calloc failure");
			ft_memcpy(padded, map->content[y], len);
			ft_memset(padded + len, ' ', map->width - len);
			free(map->content[y]);
			map->content[y] = padded;
		}
		y++;
	}
}
