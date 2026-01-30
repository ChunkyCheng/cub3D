/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:10:58 by lming-ha          #+#    #+#             */
/*   Updated: 2026/01/30 16:46:20 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	element_checklist(t_gamedata *gamedata, t_parsing *p_data)
{
	int	i;
	int	j;

	if (gamedata->texture_pack.floor == -1)
		clean_error(p_data, gamedata, "Floor color not defined");
	if (gamedata->texture_pack.ceiling == -1)
		clean_error(p_data, gamedata, "Ceiling color not defined");
	i = 0;
	while (i + 1 < 9)
	{
		j = 0;
		if (p_data->wall[i])
		{
			while (j < 4)
			{
				if (!gamedata->texture_pack.texture[i][j].file_path)
					clean_error(p_data, gamedata, "Incomplete wall set");
				j++;
			}
		}
		i++;
	}
}

static char	**strarr_add_line(char **strarr, char *line, size_t line_len)
{
	char	**new_arr;
	size_t	arr_len;
	size_t	i;

	if (!strarr)
		arr_len = 0;
	else
		arr_len = ft_strarr_len(strarr);
	new_arr = (char **)malloc(sizeof(char *) * (arr_len + 2));
	if (!new_arr)
		return (ft_strarr_free(strarr), NULL);
	i = 0;
	while (i < arr_len)
	{
		new_arr[i] = strarr[i];
		i++;
	}
	new_arr[arr_len] = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!new_arr[arr_len])
		return (ft_strarr_free(strarr), free(new_arr), NULL);
	ft_memcpy(new_arr[arr_len], line, line_len);
	new_arr[arr_len][line_len] = '\0';
	new_arr[arr_len + 1] = NULL;
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
		if (get_wall(line[i]) != 0 && !p_data->wall[get_wall(line[i])])
			clean_error(p_data, gamedata, "Undefined wall texture used in map");
		i++;
	}
	p_data->map.height++;
	p_data->map.content = strarr_add_line(p_data->map.content, line, i);
	if (p_data->map.width < i)
		p_data->map.width = i;
	if (!p_data->map.content)
		clean_error(p_data, gamedata, "Map line allocation failure");
	return (1);
}
