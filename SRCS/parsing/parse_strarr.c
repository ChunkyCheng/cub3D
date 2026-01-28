/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_strarr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:10:58 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/28 17:39:27 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#
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
	if (!line)
		return (print_error("Empty file", 0), NULL);
	while (line)
	{
		strarr = strarr_add_line(strarr, line);
		free(line);
		if (!strarr)
			return (print_error("allocation failure", 0), NULL);
		line = get_next_line(fd);
	}
	return (strarr);
}
