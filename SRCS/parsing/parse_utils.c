/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:10:27 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/30 16:05:06 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_wall(char c)
{
	if (c >= '1' && c <= '9')
		return (c - '0');
	return (0);
}

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
	if (p_data->fd > 0)
		close(p_data->fd);
	p_data->fd = -1;
	if (p_data->map.content)
		ft_strarr_free(p_data->map.content);
	if (p_data->map.mask)
		free_mask(p_data->map.mask, p_data->map.height);
	p_data->map.content = NULL;
	close_with_exit_code(gamedata, 1);
}

int	open_valid_ext(char *path, char *extension, int *out_fd)
{
	int		len;
	int		extlen;

	len = ft_strlen(path);
	extlen = ft_strlen(extension);
	if (len < extlen || ft_strncmp(&path[len - extlen], extension, extlen) != 0)
	{
		ft_putstr_fd("Error\nInvalid file extension. Expected [", 2);
		ft_putstr_fd(extension, 2);
		ft_putendl_fd("]", 2);
		return (0);
	}
	*out_fd = open(path, O_RDONLY);
	if (*out_fd < 0)
	{
		perror("Error\ncub3D");
		return (0);
	}
	return (1);
}
