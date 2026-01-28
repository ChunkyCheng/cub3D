/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gamedata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:51:14 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 17:30:55 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"
#include "parsing.h"
#include "rendering.h"

static void	init_player(t_gamedata *gamedata, int x, int y, char direction)
{
	gamedata->player.pos.x = x + 0.5;
	gamedata->player.pos.y = y + 0.5;
	if (direction == 'N')
	{
		gamedata->player.dir.y = -1;
		gamedata->player.angle = 270;
	}
	else if (direction == 'S')
	{
		gamedata->player.dir.y = 1;
		gamedata->player.angle = 90;
	}
	else if (direction == 'E')
	{
		gamedata->player.dir.x = 1;
		gamedata->player.angle = 0;
	}
	else
	{
		gamedata->player.dir.x = -1;
		gamedata->player.angle = 180;
	}
	gamedata->player.fov = DFL_FOV;
	gamedata->player.view_dist = DFL_VIEW_DIST;
}

static void	parse_map(t_gamedata *gamedata, int fd)
{
	char	*line;
	int		y;
	int		x;

	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		x = 0;
		while (line[x])
		{
			if (line[x] == '0' || line[x] == ' ')
				gamedata->map[y][x].e_type = EMPTY;
			else if (line[x] == '1')
			{
				gamedata->map[y][x].e_type = WALL;
				gamedata->map[y][x].north = &gamedata->texture_pack.wall.north;
				gamedata->map[y][x].south = &gamedata->texture_pack.wall.south;
				gamedata->map[y][x].west = &gamedata->texture_pack.wall.west;
				gamedata->map[y][x].east = &gamedata->texture_pack.wall.east;
			}
			else if (ft_strchr("NSWE", line[x]))
				init_player(gamedata, x, y, line[x]);
			x++;
		}
		y++;
		free(line);
		line = get_next_line(fd);
	}
}

// static void	parse_texture_pack(t_gamedata *gamedata, t_texture_pack *texture_pack)
// {
// 	texture_pack->wall.north.mlx_img
// 		= mlx_xpm_file_to_image(gamedata->display, DFL_NORTH,
// 			&texture_pack->wall.north.width,
// 			&texture_pack->wall.north.height);
// 	init_image_data(&texture_pack->wall.north);
// 	texture_pack->wall.south.mlx_img
// 		= mlx_xpm_file_to_image(gamedata->display, DFL_SOUTH,
// 			&texture_pack->wall.south.width,
// 			&texture_pack->wall.south.height);
// 	init_image_data(&texture_pack->wall.south);
// 	texture_pack->wall.west.mlx_img
// 		= mlx_xpm_file_to_image(gamedata->display, DFL_WEST,
// 			&texture_pack->wall.west.width,
// 			&texture_pack->wall.west.height);
// 	init_image_data(&texture_pack->wall.west);
// 	texture_pack->wall.east.mlx_img
// 		= mlx_xpm_file_to_image(gamedata->display, DFL_EAST,
// 			&texture_pack->wall.east.width,
// 			&texture_pack->wall.east.height);
// 	init_image_data(&texture_pack->wall.east);
}

void	init_gamedata(t_gamedata *gamedata, char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\ninit_gamedata");
		exit(3);
	}
	// parse_texture_pack(gamedata, &gamedata->texture_pack);
	parse_map(gamedata, fd);
	close(fd);
	init_render_vals(gamedata->render_vals);
	mlx_mouse_move(gamedata->display, gamedata->window,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
}
