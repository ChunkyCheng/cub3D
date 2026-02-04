/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:10:58 by lming-ha          #+#    #+#             */
/*   Updated: 2026/02/04 14:44:45 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
	i = -1;
	while (++i < arr_len)
		new_arr[i] = strarr[i];
	new_arr[arr_len] = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!new_arr[arr_len])
		return (ft_strarr_free(strarr), free(new_arr), NULL);
	ft_memcpy(new_arr[arr_len], line, line_len);
	new_arr[arr_len][line_len] = '\0';
	new_arr[arr_len + 1] = NULL;
	free(strarr);
	return (new_arr);
}

static void	set_coin_door(t_gamedata *gamedata, t_parsing *p_data,
		t_image *textures, char **paths)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (paths[i] == NULL)
			clean_error(p_data, gamedata, "Texture path undefined");
		set_texture(gamedata, p_data, &textures[i], paths[i]);
		i++;
	}
}

static void	init_coin_door(t_gamedata *gamedata, t_parsing *p_data, char c)
{
	char	*paths[4];

	if (!gamedata->texture_pack.coin_frames[0].file_path && c == 'C')
	{
		paths[0] = COIN0;
		paths[1] = COIN1;
		paths[2] = COIN2;
		paths[3] = COIN3;
		set_coin_door(gamedata, p_data,
			gamedata->texture_pack.coin_frames, paths);
	}
	else if (!gamedata->texture_pack.texture[0][0].file_path && c == 'D')
	{
		paths[0] = DOOR_N;
		paths[1] = DOOR_S;
		paths[2] = DOOR_W;
		paths[3] = DOOR_E;
		set_coin_door(gamedata, p_data,
			gamedata->texture_pack.texture[0], paths);
	}
}

static void	empty_map_line(t_parsing *p_data, t_gamedata *gamedata, int height)
{
	static int	first_nl = -1;

	if (height > 0 && first_nl == -1)
		first_nl = p_data->map.height;
	if (height != first_nl)
		clean_error(p_data, gamedata, "Empty line in map");
}

void	add_map_line(char *line, t_parsing *p_data, t_gamedata *gamedata)
{
	int	i;

	i = 0;
	if (line[0] == '\n')
	{
		empty_map_line(p_data, gamedata, p_data->map.height);
		return ;
	}
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && ft_strchr(" NSEWCD", line[i]) == NULL)
			clean_error(p_data, gamedata, "Invalid character in map");
		if (ft_strchr("CD", line[i]))
			init_coin_door(gamedata, p_data, line[i]);
		if (get_wall(line[i]) != 0 && !p_data->txt[get_wall(line[i])])
			clean_error(p_data, gamedata, "Undefined wall texture used in map");
		i++;
	}
	p_data->map.height++;
	p_data->map.content = strarr_add_line(p_data->map.content, line, i);
	if (p_data->map.width < i)
		p_data->map.width = i;
	if (!p_data->map.content)
		clean_error(p_data, gamedata, "Map line allocation failure");
	return ;
}
