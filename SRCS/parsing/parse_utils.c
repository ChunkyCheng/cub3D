/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:10:27 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/28 17:50:44 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	parsing_cleanup(t_parsing *p_data)
{
	if (p_data->identifier)
		free(p_data->identifier);
	if (p_data->info)
		free(p_data->info);
	p_data->identifier = NULL;
	p_data->info = NULL;
	p_data->wall_idx = 0;
}

void	clean_error(t_parsing *p_data, t_gamedata *gamedata, char *message)
{
	if (message)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(message, 2);
	}
	parsing_cleanup(p_data);
	if (p_data->file)
		ft_strarr_free(p_data->file);
	p_data->file = NULL;
	close_with_exit_code(gamedata, 1);
}

int	read_valid_ext(char *path, char *extension, char ***file)
{
	int		len;
	int		extlen;
	int		fd;

	len = ft_strlen(path);
	extlen = ft_strlen(extension);
	if (len < extlen || ft_strncmp(&path[len - extlen], extension, extlen) != 0)
	{
		ft_putendl_fd("Error\nInvalid file extension. Expected [", 2);
		ft_putendl_fd(extension, 2);
		ft_putendl_fd("]", 2);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Error\ncub3D"), 0);
	if (file)
	{
		*file = file_to_strarr(fd);
		if (!*file)
			return (close(fd), 0);
	}
	close(fd);
	return (1);
}
