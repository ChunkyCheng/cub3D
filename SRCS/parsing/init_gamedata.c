/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gamedata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:51:14 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/03 17:57:25 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"
#include "parsing.h"
#include "rendering.h"

static void	set_map_cell(t_gamedata *gamedata, t_map *pmap, int **mask, int x, int y)
{
	int	t_idx;

	t_idx = get_wall(pmap->content[y][x]);
	if (pmap->content[y][x] == ' ' && mask[y][x] == 3)
		gamedata->map[y][x].e_type = UNBOUND;
	else if (ft_strchr(" 0", pmap->content[y][x]))
		gamedata->map[y][x].e_type = EMPTY;
	if (pmap->content[y][x] == 'D' || t_idx)
	{
		if (gamedata->pmap.content[y][x] == 'D')
			gamedata->map[y][x].e_type = DOOR;
		else
			gamedata->map[y][x].e_type = WALL;
		gamedata->map[y][x].north = &gamedata->texture_pack.texture[t_idx][0];
		gamedata->map[y][x].south = &gamedata->texture_pack.texture[t_idx][1];
		gamedata->map[y][x].west = &gamedata->texture_pack.texture[t_idx][2];
		gamedata->map[y][x].east = &gamedata->texture_pack.texture[t_idx][3];
		gamedata->map[y][x].solid = 1;
		gamedata->map[y][x].visible = 1;
	}
	if (pmap->content[y][x] == 'C')
		add_coin(gamedata, &gamedata->coins, x, y);
}

static void	arr_to_map_cell(t_gamedata *gamedata, t_map *pmap, int **mask)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAP_SIZE_MAX)
	{
		x = 0;
		while (x < MAP_SIZE_MAX)
		{
			if (y < pmap->height && x < pmap->width)
				set_map_cell(gamedata, pmap, mask, x, y);
			else
				gamedata->map[y][x].e_type = UNBOUND;
			x++;
		}
		y++;
	}
	ft_strarr_free(pmap->content);
	pmap->content = NULL;
}

static void	init_tex_pack(t_gamedata *gamedata, t_texture_pack *texture_pack)
{
	int	i;
	int	j;

	gamedata->texture_pack.texture[0][0].file_path = DFL_NORTH;
	gamedata->texture_pack.texture[0][1].file_path = DFL_SOUTH;
	gamedata->texture_pack.texture[0][2].file_path = DFL_WEST;
	gamedata->texture_pack.texture[0][3].file_path = DFL_EAST;
	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 4)
		{
			if (!gamedata->texture_pack.texture[i][j].file_path)
				break ;
			init_image_data(&texture_pack->texture[i][j], gamedata);
			j++;
		}
		i++;
	}
	init_image_data(&texture_pack->coin_frames[0], gamedata);
	init_image_data(&texture_pack->coin_frames[1], gamedata);
	init_image_data(&texture_pack->coin_frames[2], gamedata);
	init_image_data(&texture_pack->coin_frames[3], gamedata);
}

void	init_gamedata(t_gamedata *gamedata)
{
	gamedata->texture_pack.coin_frames[0].file_path = COIN0;
	gamedata->texture_pack.coin_frames[1].file_path = COIN1;
	gamedata->texture_pack.coin_frames[2].file_path = COIN2;
	gamedata->texture_pack.coin_frames[3].file_path = COIN3;
	init_tex_pack(gamedata, &gamedata->texture_pack);
	init_coin_animation(gamedata, &gamedata->texture_pack, &gamedata->coins);
	arr_to_map_cell(gamedata, &gamedata->pmap, gamedata->pmap.mask);
	free_mask(gamedata->pmap.mask, gamedata->pmap.height);
	gamedata->pmap.mask = NULL;
	init_cache(gamedata, gamedata->cache);
	mlx_mouse_move(gamedata->display, gamedata->window,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
}
