/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:19:44 by lming-ha          #+#    #+#             */
/*   Updated: 2026/02/02 15:52:22 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	**dup_mask(t_map *map, t_parsing *p_data, t_gamedata *gamedata)
{
	int	**new_mask;
	int	y;

	new_mask = ft_calloc(map->height, sizeof(int *));
	if (!new_mask)
		clean_error(p_data, gamedata, "ft_calloc failure");
	y = 0;
	while (y < map->height)
	{
		new_mask[y] = ft_calloc(map->width, sizeof(int));
		if (!new_mask[y])
			clean_error(p_data, gamedata, "ft_calloc failure");
		ft_memcpy(new_mask[y], map->mask[y], sizeof(int) * map->width);
		y++;
	}
	return (new_mask);
}

static void	parse_map(t_gamedata *gamedata, t_parsing *p_data)
{
	pad_map(&p_data->map, p_data, gamedata);
	trim_map(&p_data->map, p_data, gamedata);
	parse_player(gamedata, p_data);
	validate_map(gamedata, p_data);
	parsing_cleanup(p_data);
	close(p_data->fd);
	p_data->fd = -1;
	gamedata->pmap.content = ft_strarr_dup(p_data->map.content);
	if (!gamedata->pmap.content)
		clean_error(p_data, gamedata, "ft_strarr_dup failure");
	gamedata->pmap.height = p_data->map.height;
	gamedata->pmap.width = p_data->map.width;
	gamedata->pmap.mask = dup_mask(&p_data->map, p_data, gamedata);
	if (!gamedata->pmap.mask)
		clean_error(p_data, gamedata, "dup_mask failure");
	p_data->map.content = NULL;
	free_mask(p_data->map.mask, p_data->map.height);
	p_data->map.mask = NULL;
}

static void	parse_line(char *line, t_gamedata *gamedata, t_parsing *p_data)
{
	if (p_data->e_state == ELEMENTS && line[0] != '\n')
		parse_element(line, gamedata, p_data);
	if (p_data->e_state == MAP)
	{
		if (line[0] == '\n')
			clean_error(p_data, gamedata, "Map contains empty lines");
		element_checklist(gamedata, p_data);
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
	p_data.fd = open(map_path, O_RDONLY);
	parse_map(gamedata, &p_data);
}
