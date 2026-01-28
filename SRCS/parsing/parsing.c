/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:19:44 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/28 18:02:58 by lming-ha         ###   ########.fr       */
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

void	parse_map_line(char *line, t_gamedata *gamedata, t_parsing *p_data)
{
	check_texture_complete(gamedata, p_data);
}

void	parse_content(t_parsing *p_data, t_gamedata *gamedata)
{
	size_t	i;
	char	*line;

	i = 0;
	while (p_data->file[i])
	{
		line = p_data->file[i];
		if (p_data->e_state == ELEMENTS && p_data->file[i][0] != '\n')
			parse_element(line, gamedata, p_data);
		line = p_data->file[i];
		if (p_data->e_state == MAP)
			parse_map_line(line, gamedata, p_data);
		i++;
	}
	return (1);
}

void	parsing(t_gamedata *gamedata, char *map_path)
{
	t_parsing	p_data;

	p_data = (t_parsing){0};
	p_data.e_state = ELEMENTS;
	if (!read_valid_ext(map_path, ".cub", &p_data.file))
		close_with_exit_code(gamedata, 1);
	gamedata->texture_pack.floor = -1;
	gamedata->texture_pack.ceiling = -1;
	parse_content(&p_data, gamedata);
	parsing_cleanup(&p_data);
	return (1);
}
