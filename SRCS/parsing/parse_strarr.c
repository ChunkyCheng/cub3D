/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_strarr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:10:58 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/29 18:32:40 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int	add_map_line(char *line, t_parsing *p_data, t_gamedata *gamedata)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && ft_strchr(" NSEWCD", line[i]) == NULL)
			clean_error(p_data, gamedata, "Invalid character in map");
		i++;
	}
	p_data->map.height++;
	if (p_data->map.width < i)
		p_data->map.width = i;
	p_data->map.content = strarr_add_line(p_data->map.content, line);
	if (!p_data->map.content)
		clean_error(p_data, gamedata, "Map line allocation failure");
	return (1);
}
