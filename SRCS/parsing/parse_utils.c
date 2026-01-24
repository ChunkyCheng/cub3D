/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:49:55 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/24 18:32:28 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

int	print_error(char *message, int	exit_code)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	return (exit_code);
}

static char	**strarr_add_line(char **strarr, char *line)
{
	char	**new_arr;
	size_t	len;
	size_t	i;

	if (!strarr)
		len = 0;
	else
		len = ft_strarr_len(strarr);
	new_arr = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (ft_strarr_free(strarr), NULL);
	i = 0;
	while (i < len)
	{
		new_arr[i] = strarr[i];
		i++;
	}
	new_arr[i] = ft_strdup(line);
	if (!new_arr[i])
		return (ft_strarr_free(strarr), free(new_arr), NULL);
	new_arr[i + 1] = NULL;
	free(strarr);
	return (new_arr);
}

char	**file_to_strarr(int fd)
{
	char	**strarr;
	char	*line;

	strarr = NULL;
	line = get_next_line(fd);
	while (line)
	{
		strarr = strarr_add_line(strarr, line);
		free(line);
		if (!strarr)
			return (NULL);
		line = get_next_line(fd);
	}
	return (strarr);
}
