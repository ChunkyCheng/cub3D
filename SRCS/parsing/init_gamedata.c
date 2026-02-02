/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gamedata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:51:14 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 16:57:57 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"
#include "parsing.h"
#include "rendering.h"

static void	set_wall_cell(t_gamedata *gamedata, int x, int y, int t_idx)
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

static void	arr_to_map_cell(t_gamedata *gamedata, t_map *pmap, int **mask)
{
	int		y;
	int		x;
	int		t_idx;

	y = 0;
	while (y < pmap->height)
	{
		x = 0;
		while (x < pmap->width && pmap->content[y][x])
		{
			t_idx = get_wall(pmap->content[y][x]);
			if (pmap->content[y][x] == ' ' && mask[y][x] == 3)
				gamedata->map[y][x].e_type = UNBOUND;
			else if (ft_strchr(" 0", pmap->content[y][x]))
				gamedata->map[y][x].e_type = EMPTY;
			if (pmap->content[y][x] == 'D' || t_idx)
				set_wall_cell(gamedata, x, y, t_idx);
			if (pmap->content[y][x] == 'C')
				add_coin(&gamedata->coins, x, y);
			x++;
		}
		y++;
	}
}

static void	init_image_data(t_image *image, t_gamedata *gamedata)
{
	if (!image->mlx_img)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putendl_fd(image->file_path, 2);
		close_with_exit_code(gamedata, 127);
	}
	image->pixels = mlx_get_data_addr(image->mlx_img, &image->bitsperpixel,
			&image->row_len, &image->endian);
	if (!image->pixels)
	{
		ft_putstr_fd("Error\nFailed to get image data address", 2);
		close_with_exit_code(gamedata, 127);
	}
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
			texture_pack->texture[i][j].mlx_img
				= mlx_xpm_file_to_image(gamedata->display,
					texture_pack->texture[i][j].file_path,
					&texture_pack->texture[i][j].width,
					&texture_pack->texture[i][j].height);
			init_image_data(&texture_pack->texture[i][j], gamedata);
			j++;
		}
		i++;
	}
}

void	init_gamedata(t_gamedata *gamedata, char *map_path)
{
	(void)map_path;
	init_tex_pack(gamedata, &gamedata->texture_pack);
	arr_to_map_cell(gamedata, &gamedata->pmap, gamedata->pmap.mask);
	init_render_vals(gamedata->render_vals);
	mlx_mouse_move(gamedata->display, gamedata->window,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
}
