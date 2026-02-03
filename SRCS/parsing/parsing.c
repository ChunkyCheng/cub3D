/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:19:44 by lming-ha          #+#    #+#             */
/*   Updated: 2026/02/03 15:55:36 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	parse_map(t_gamedata *gamedata, t_parsing *p_data)
{
	pad_map(&p_data->map, p_data, gamedata);
	trim_map(&p_data->map, p_data, gamedata);
	parse_player(gamedata, p_data);
	validate_map(gamedata, p_data);
	parsing_cleanup(p_data);
	gamedata->pmap.content = p_data->map.content;
	gamedata->pmap.mask = p_data->map.mask;
	p_data->map.mask = NULL;
	gamedata->pmap.height = p_data->map.height;
	gamedata->pmap.width = p_data->map.width;
}

static void	parse_file(t_gamedata *gamedata, t_parsing *p_data)
{
	char	*line;

	line = get_next_line(p_data->fd);
	if (!line)
		clean_error(p_data, gamedata, "Empty file");
	while (line)
	{
		p_data->cur_line = line;
		if (p_data->e_state == ELEMENTS && line[0] != '\n')
			parse_element(line, gamedata, p_data);
		if (p_data->e_state == MAP)
		{
			element_checklist(gamedata, p_data);
			add_map_line(line, p_data, gamedata);
		}
		free(line);
		line = get_next_line(p_data->fd);
	}
	p_data->cur_line = NULL;
	close(p_data->fd);
	p_data->fd = -1;
	if (p_data->e_state != MAP)
		clean_error(p_data, gamedata, "No map data found");
}

void	parsing(t_gamedata *gamedata, char *map_path)
{
	t_parsing	p_data;

	p_data = (t_parsing){0};
	p_data.fd = -1;
	p_data.e_state = ELEMENTS;
	gamedata->texture_pack.floor = -1;
	gamedata->texture_pack.ceiling = -1;
	if (!open_valid_ext(map_path, ".cub", &p_data.fd))
		close_with_exit_code(gamedata, 1);
	parse_file(gamedata, &p_data);
	parse_map(gamedata, &p_data);
}
