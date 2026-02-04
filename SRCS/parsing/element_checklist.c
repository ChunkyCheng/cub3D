/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_checklist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:33:18 by lming-ha          #+#    #+#             */
/*   Updated: 2026/02/04 14:38:28 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	check_texture_set(t_gamedata *gamedata, t_parsing *p_data,
	t_image *texture, int *checked)
{
	int	j;

	if (*checked)
		return ;
	j = 0;
	while (j < 4)
	{
		if (!texture[j].file_path)
			clean_error(p_data, gamedata, "Incomplete texture set");
		j++;
	}
}

void	element_checklist(t_gamedata *gamedata, t_parsing *p_data)
{
	int			i;
	static int	checked[TEXTURES + 1] = {0};

	i = 0;
	while (i < TEXTURES)
	{
		if (p_data->txt[i])
		{
			check_texture_set(gamedata, p_data,
				gamedata->texture_pack.texture[i], &checked[i]);
			checked[i] = 1;
		}
		i++;
	}
	if (gamedata->texture_pack.floor == -1)
		clean_error(p_data, gamedata, "Floor color not defined");
	if (gamedata->texture_pack.ceiling == -1)
		clean_error(p_data, gamedata, "Ceiling color not defined");
	if (gamedata->texture_pack.coin_frames[0].file_path)
	{
		check_texture_set(gamedata, p_data, gamedata->texture_pack.coin_frames,
			&checked[TEXTURES]);
		checked[TEXTURES] = 1;
	}
}
