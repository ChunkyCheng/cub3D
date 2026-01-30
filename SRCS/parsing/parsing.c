/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:19:44 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/30 16:53:36 by lming-ha         ###   ########.fr       */
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
	close(p_data->fd);
	p_data->fd = -1;
	ft_strarr_free(p_data->map.content);
	p_data->map.content = NULL;
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
	parse_map(gamedata, &p_data);
}
