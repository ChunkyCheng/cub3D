/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:09:55 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/28 17:52:57 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	parse_info(t_gamedata *gamedata, t_parsing *p_data)
{
	int			i;
	const char	*wall[4] = {"NO", "EA", "SO", "WE"};

	i = 0;
	if (*p_data->identifier == 'F' || *p_data->identifier == 'C')
		return (parse_colour(gamedata, p_data));
	if (!ft_strchr(p_data->info, '/'))
		clean_error(p_data, gamedata, "Texture information is not a path");
	while (i < 4)
	{
		if (ft_strncmp(p_data->identifier, wall[i], 2) == 0)
		{
			if (gamedata->texture_pack.wall[p_data->wall_idx][i].mlx_img)
				clean_error(p_data, gamedata, "Duplicate wall definition");
			if (read_valid_ext(p_data->info, ".xpm", NULL) == 0)
				clean_error(p_data, gamedata, NULL);
			gamedata->texture_pack.wall[p_data->wall_idx][i].file_path
				= ft_strdup(p_data->info);
			if (!gamedata->texture_pack.wall[p_data->wall_idx][i].file_path)
				clean_error(p_data, gamedata, "ft_strdup failure");
			return ;
		}
		i++;
	}
}

static void	parse_identifier(t_parsing *p_data, t_gamedata *gd, char **line)
{
	if (*p_data->identifier != 'F' && *p_data->identifier != 'C')
	{
		if (**line >= '1' && **line <= '9')
		{
			p_data->wall_idx = ft_atoi(**line);
			(*line)++;
		}
		else if (**line == ' ')
			p_data->wall_idx = 1;
		else
			clean_error(p_data, gd, "Invalid wall texture suffix");
		p_data->wall_idx -= 1;
		p_data->wall[p_data->wall_idx] = 1;
		p_data->identifier = ft_substr(p_data->identifier, 0, 2);
		if (!p_data->identifier)
			clean_error(p_data, gd, "ft_substr failure");
	}
	if (**line != ' ')
		clean_error(p_data, gd, "No separator after type identifier");
}

static int	identify_element(char **line, t_parsing *p_data, t_gamedata *gd)
{
	int			i;
	int			found;
	const char	*identifiers[6] = {"NO", "EA", "SO", "WE", "F", "C"};

	i = 0;
	found = 0;
	while (i < 6)
	{
		if (ft_strncmp(*line, identifiers[i], ft_strlen(identifiers[i])) == 0)
		{
			p_data->identifier = (char *)identifiers[i];
			*line += ft_strlen(identifiers[i]);
			found = 1;
		}
		i++;
	}
	if (found)
		parse_identifier(p_data, gd, line);
	while (line && **line == ' ')
		(*line)++;
	if (!found && (**line == '1' || **line == '0'
			|| **line == '\n' || **line == '\0'))
		return (p_data->e_state = MAP, 1);
	return (found);
}

void	parse_element(char *line, t_gamedata *gamedata, t_parsing *p_data)
{
	if (*line == ' ' || *line == '1' || *line == '0')
	{
		p_data->e_state = MAP;
		return ;
	}
	if (!identify_element(&line, p_data, gamedata))
		clean_error(p_data, gamedata, "Invalid element line");
	if (p_data->e_state == MAP)
		return ;
	p_data->info = ft_strtrim(line, "\n");
	if (!p_data->info)
		clean_error(p_data, gamedata, "ft_strtrim failure");
	if (ft_strlen(p_data->info) == 0)
		clean_error(p_data, gamedata, "No specific information provided");
	parse_info(gamedata, p_data);
	parsing_cleanup(p_data);
}
