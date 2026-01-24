/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:19:44 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/24 21:00:08 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

int	process_identifier(char **line, t_state *state)
{
	int			i;
	const char	*texture[6] = {"NO ", "EA ", "SO ", "WE ", "F ", "C "};

	if (**line == ' ' || **line == '1' || **line == '0')
		*state = MAP;
	while (line && **line == ' ')
		(*line)++;
	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(*line, texture[i], ft_strlen(texture[i])) == 0)
		{
			*state = ELEMENTS;
			*line += ft_strlen(texture[i]);
			return (1);
		}
		i++;
	}
	if (**line != '1' && **line != '0' && **line != '\n' && **line != '\0')
		*state = ELEMENTS;
	return (*state == MAP);
}

int	parse_element_line(char *line, t_gamedata *gamedata, t_state *state)
{
	char	*texture_path;

	if (line[0] == '\n' && line[1] == '\0')
		return (1);
	if (!process_identifier(&line, state))
		return (print_error("Invalid type identifier or no separator", 0));
	if (*state == MAP)
		return (1);
	texture_path = ft_strtrim(line, " \n");
	if (!texture_path)
		return (print_error("ft_strtrim failure", 0));
	if (ft_strlen(texture_path) == 0)
		return (free(texture_path), print_error("No texture path", 0));
	free(texture_path);
}

int	parse_content(char **map, t_gamedata *gamedata)
{
	t_state	state;
	size_t	i;

	state = ELEMENTS;
	i = 0;
	while (map[i])
	{
		if (state == ELEMENTS)
		{
			if (!parse_element_line(map[i], gamedata, &state))
				return (0);
		}
		else if (state == MAP)
		{
			if (!is_map_line(map[i]))
				return (print_error("Invalid map format", 0));
		}
		i++;
	}
	return (1);
}

int	parse_args(t_gamedata *gamedata, char *map_path)
{
	int		len;
	int		fd;
	char	**map;

	len = ft_strlen(map_path);
	if (len < 4 || ft_strncmp(&map_path[len] - 4, ".cub", 4) != 0)
		return (print_error("Invalid file extension. Expected [.cub]", 0));
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error\ncub3D"), 0);
	map = file_to_strarr(fd);
	close(fd);
	if (!map)
		return (print_error("Empty or invalid file", 0));
	if (!parse_content(map, gamedata))
	{
		ft_strarr_free(map);
		return (0);
	}
	ft_strarr_free(map);
	return (0);
}
