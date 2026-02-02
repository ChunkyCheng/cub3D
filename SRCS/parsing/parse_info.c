/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:10:09 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/30 09:25:32 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	rgbtoi(const char *str)
{
	int	digit;
	int	value;

	digit = 0;
	value = 0;
	while (str[digit])
	{
		if (!ft_isdigit(str[digit]))
		{
			ft_putendl_fd("Error\nR,G,B values must consist of only digits", 2);
			return (-1);
		}
		digit++;
	}
	if (digit == 0 || digit > 3)
	{
		ft_putendl_fd("Error\nR,G,B values can only have 1 to 3 digits", 2);
		return (-1);
	}
	value = ft_atoi(str);
	if (value < 0 || value > 255)
		return (ft_putendl_fd("Error\nRGB value out of range [0,255]", 2), -1);
	return (value);
}

static int	parse_rgb_color(char *info, t_parsing *p_data, t_gamedata *gamedata)
{
	int		r;
	int		g;
	int		b;
	char	**rgb_values;

	rgb_values = ft_split(info, ",");
	if (!rgb_values)
		clean_error(p_data, gamedata, "ft_split failure");
	if (!rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
	{
		ft_strarr_free(rgb_values);
		clean_error(p_data, gamedata, "Invalid R,G,B color format");
	}
	r = rgbtoi(rgb_values[0]);
	g = rgbtoi(rgb_values[1]);
	b = rgbtoi(rgb_values[2]);
	ft_strarr_free(rgb_values);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	return (r << 16 | g << 8 | b);
}

void	parse_colour(t_gamedata *gamedata, t_parsing *p_data)
{
	int	colour;

	if (*p_data->identifier == 'F' && gamedata->texture_pack.floor != -1)
		return (clean_error(p_data, gamedata, "Duplicate floor definition"));
	if (*p_data->identifier == 'C' && gamedata->texture_pack.ceiling != -1)
		return (clean_error(p_data, gamedata, "Duplicate ceiling definition"));
	colour = parse_rgb_color(p_data->info, p_data, gamedata);
	if (colour == -1)
		clean_error(p_data, gamedata, NULL);
	if (*p_data->identifier == 'F')
		gamedata->texture_pack.floor = colour;
	else
		gamedata->texture_pack.ceiling = colour;
}

void	parse_texture(t_gamedata *gamedata, t_parsing *p_data)
{
	int			i;
	int			fd;
	const char	*wall[4] = {"NO", "EA", "SO", "WE"};

	i = -1;
	fd = -1;
	if (!ft_strchr(p_data->info, '/'))
		clean_error(p_data, gamedata, "Texture information is not a path");
	while (i++ < 3)
	{
		if (ft_strncmp(p_data->identifier, wall[i], 2) == 0)
		{
			if (gamedata->texture_pack.texture[p_data->wall_idx][i].file_path)
				clean_error(p_data, gamedata, "Duplicate wall definition");
			if (open_valid_ext(p_data->info, ".xpm", &fd) == 0)
				clean_error(p_data, gamedata, NULL);
			close(fd);
			gamedata->texture_pack.texture[p_data->wall_idx][i].file_path
				= ft_strdup(p_data->info);
			if (!gamedata->texture_pack.texture[p_data->wall_idx][i].file_path)
				clean_error(p_data, gamedata, "ft_strdup failure");
		}
	}
}
