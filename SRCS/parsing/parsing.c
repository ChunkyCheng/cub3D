/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:19:44 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/29 18:37:34 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_texture_complete(t_gamedata *gamedata, t_parsing *p_data)
{
	int	i;
	int	j;

	if (gamedata->texture_pack.floor == -1)
		clean_error(p_data, gamedata, "Floor color not defined");
	if (gamedata->texture_pack.ceiling == -1)
		clean_error(p_data, gamedata, "Ceiling color not defined");
	i = 0;
	while (i < 8)
	{
		j = 0;
		if (p_data->wall[i])
		{
			while (j < 4)
			{
				if (!gamedata->texture_pack.wall[i][j].file_path)
					clean_error(p_data, gamedata, "Incomplete wall set");
				j++;
			}
		}
		i++;
	}
}

static void	pad_map(t_map *map, t_parsing *p_data, t_gamedata *gamedata)
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

static int	row_empty(char *row, int left, int right)
{
	while (left <= right)
	{
		if (row[left] != ' ' && row[left] != '\n' && row[left] != '\0')
			return (0);
		left++;
	}
	return (1);
}

static int	col_empty(t_map *map, int col, int top, int bottom)
{
	while (top <= bottom)
	{
		if (map->content[top][col] != ' ' && map->content[top][col] != '\n' && map->content[top][col] != '\0')
			return (0);
		top++;
	}
	return (1);
}

static void	trim_map_borders(t_map *map)
{
	int	top;
	int	bottom;
	int	left;
	int	right;

	top = 0;
	bottom = map->height - 1;
	left = 0;
	right = map->width - 1;
	while (top <= bottom && row_empty(map->content[top], left, right))
		top++;
	while (bottom > top && row_empty(map->content[bottom], left, right))
		bottom--;
	while (left <= right && col_empty(map, left, top, bottom))
		left++;
	while (right > left && col_empty(map, right, top, bottom))
		right--;
	map->top = top;
	map->bottom = bottom;
	map->left = left;
	map->right = right;
}

static void	parse_map(t_gamedata *gamedata, t_parsing *p_data)
{
	pad_map(&p_data->map, p_data, gamedata);
	trim_map_borders(&p_data->map);
	parse_player(gamedata, p_data);
}

static void	parse_line(char *line, t_gamedata *gamedata, t_parsing *p_data)
{
	if (p_data->e_state == ELEMENTS && line[0] != '\n')
		parse_element(line, gamedata, p_data);
	if (p_data->e_state == MAP)
	{
		if (line[0] == '\n')
			clean_error(p_data, gamedata, "Map contains empty lines");
		check_texture_complete(gamedata, p_data);
		add_map_line(line, p_data, gamedata);
	}
}

void	parsing(t_gamedata *gamedata, char *map_path)
{
	t_parsing	p_data;
	char		*line;

	p_data = (t_parsing){0};
	p_data.fd = -1;
	p_data.e_state = ELEMENTS;
	gamedata->texture_pack.floor = -1;
	gamedata->texture_pack.ceiling = -1;
	if (!open_valid_ext(map_path, ".cub", &p_data.fd))
		close_with_exit_code(gamedata, 1);
	line = get_next_line(p_data.fd);
	if (!line)
		clean_error(&p_data, gamedata, "Empty file");
	while (line)
	{
		parse_line(line, gamedata, &p_data);
		free(line);
		line = get_next_line(p_data.fd);
	}
	close(p_data.fd);
	p_data.fd = -1;
	if (p_data.e_state != MAP)
		clean_error(&p_data, gamedata, "No map data found");
	parse_map(gamedata, &p_data);
}
