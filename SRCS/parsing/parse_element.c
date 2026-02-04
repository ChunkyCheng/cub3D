/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:09:55 by lming-ha          #+#    #+#             */
/*   Updated: 2026/02/04 13:30:05 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	parse_found(t_parsing *p_data, t_gamedata *gamedata, char **line)
{
	if (*p_data->identifier != 'F' && *p_data->identifier != 'C')
	{
		if (get_wall(**line))
		{
			p_data->wall_idx = get_wall(**line);
			(*line)++;
		}
		else if (**line == ' ')
			p_data->wall_idx = 1;
		else
			clean_error(p_data, gamedata, "Invalid wall texture suffix");
		p_data->txt[p_data->wall_idx] = 1;
	}
	if (**line != ' ')
		clean_error(p_data, gamedata, "No separator after type identifier");
}

static int	find_element(char **line, t_parsing *p_data, t_gamedata *gamedata)
{
	int			i;
	int			found;
	const char	*identifiers[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	i = 0;
	found = 0;
	while (i < 6)
	{
		if (ft_strncmp(*line, identifiers[i], ft_strlen(identifiers[i])) == 0)
		{
			p_data->identifier = ft_substr(*line, 0, ft_strlen(identifiers[i]));
			if (!p_data->identifier)
				clean_error(p_data, gamedata, "ft_substr failure");
			*line += ft_strlen(identifiers[i]);
			found = 1;
		}
		i++;
	}
	if (found)
		parse_found(p_data, gamedata, line);
	while (line && **line == ' ')
		(*line)++;
	return (found);
}

void	parse_element(char *line, t_gamedata *gamedata, t_parsing *p_data)
{
	int	element;

	if (*line == ' ' || *line == '1')
	{
		p_data->e_state = MAP;
		return ;
	}
	element = find_element(&line, p_data, gamedata);
	if (!element && (ft_strchr("123456789\n", *line) || *line == '\0'))
	{
		p_data->e_state = MAP;
		return ;
	}
	else if (!element)
		clean_error(p_data, gamedata, "Invalid element line");
	p_data->info = ft_strtrim(line, "\n");
	if (!p_data->info)
		clean_error(p_data, gamedata, "ft_strtrim failure");
	if (ft_strlen(p_data->info) == 0)
		clean_error(p_data, gamedata, "No specific information provided");
	if (*p_data->identifier == 'F' || *p_data->identifier == 'C')
		parse_colour(gamedata, p_data);
	else
		parse_texture(gamedata, p_data);
	parsing_cleanup(p_data);
}
