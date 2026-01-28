/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gamedata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:51:14 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 22:56:53 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"
#include "parsing.h"
#include "rendering.h"

static int	is_valid_path(char *map_path)
{
	int	len;

	len = ft_strlen(map_path);
	if (len < 5 || ft_strcmp(&map_path[len] - 4, ".cub"))
		return (0);
	return (1);
}

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

static void	add_coin(t_coins *coins, int x, int y)
{
	coins->pos[coins->coin_total] = (t_vect){.x = x + 0.5, .y = y + 0.5};
	coins->coin_total++;
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
			{
				gamedata->map[y][x].e_type = EMPTY;
				gamedata->map[y][x].solid = 0;
				gamedata->map[y][x].visible = 0;
			}
			else if (line[x] == '1' || line[x] == 'D')
			{
				if (line[x] == 'D')
					gamedata->map[y][x].e_type = DOOR;
				else
					gamedata->map[y][x].e_type = WALL;
				gamedata->map[y][x].north = &gamedata->texture_pack.wall1.north;
				gamedata->map[y][x].south = &gamedata->texture_pack.wall1.south;
				gamedata->map[y][x].west = &gamedata->texture_pack.wall1.west;
				gamedata->map[y][x].east = &gamedata->texture_pack.wall1.east;
				gamedata->map[y][x].solid = 1;
				gamedata->map[y][x].visible = 1;
			}
			else if (ft_strchr("NSWE", line[x]))
				init_player(gamedata, x, y, line[x]);
			else if (line[x] == 'C')
				add_coin(&gamedata->coins, x, y);
			x++;
		}
		y++;
		free(line);
		line = get_next_line(fd);
	}
}

static void	parse_texture_pack(t_gamedata *gamedata,
t_texture_pack *texture_pack, int fd)
{
	(void)fd;
	texture_pack->floor = DFL_FLOOR;
	texture_pack->ceiling = DFL_CEILING;
	texture_pack->wall1.north.mlx_img
		= mlx_xpm_file_to_image(gamedata->display, DFL_NORTH,
			&texture_pack->wall1.north.width,
			&texture_pack->wall1.north.height);
	init_image_data(&texture_pack->wall1.north);
	texture_pack->wall1.south.mlx_img
		= mlx_xpm_file_to_image(gamedata->display, DFL_SOUTH,
			&texture_pack->wall1.south.width,
			&texture_pack->wall1.south.height);
	init_image_data(&texture_pack->wall1.south);
	texture_pack->wall1.west.mlx_img
		= mlx_xpm_file_to_image(gamedata->display, DFL_WEST,
			&texture_pack->wall1.west.width,
			&texture_pack->wall1.west.height);
	init_image_data(&texture_pack->wall1.west);
	texture_pack->wall1.east.mlx_img
		= mlx_xpm_file_to_image(gamedata->display, DFL_EAST,
			&texture_pack->wall1.east.width,
			&texture_pack->wall1.east.height);
	init_image_data(&texture_pack->wall1.east);
}

static void	parse_coin_animation(t_gamedata *gamedata, t_coins *coins)
{
	coins->frames[0].mlx_img = mlx_xpm_file_to_image(gamedata->display, COIN0,
		&coins->frames[0].width, &coins->frames[0].height);
	init_image_data(&coins->frames[0]);
	coins->frames[1].mlx_img = mlx_xpm_file_to_image(gamedata->display, COIN1,
		&coins->frames[1].width, &coins->frames[1].height);
	init_image_data(&coins->frames[1]);
	coins->frames[2].mlx_img = mlx_xpm_file_to_image(gamedata->display, COIN2,
		&coins->frames[2].width, &coins->frames[2].height);
	init_image_data(&coins->frames[2]);
	coins->frames[3].mlx_img = mlx_xpm_file_to_image(gamedata->display, COIN3,
		&coins->frames[3].width, &coins->frames[3].height);
	init_image_data(&coins->frames[3]);
	coins->frames[4] = coins->frames[0];
	coins->frames[5] = coins->frames[0];
	coins->frames[6] = coins->frames[0];
	coins->frames[7] = coins->frames[0];
	coins->frame_total = 8;
	coins->frame_current = 0;
	coins->frame_delay = 10;
}

void	init_gamedata(t_gamedata *gamedata, char *map_path)
{
	int	fd;

	if (!is_valid_path(map_path))
	{
		ft_putstr_fd("Error\ninvalid file extension\n", 2);
		exit(2);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\ninit_gamedata");
		exit(3);
	}
	parse_texture_pack(gamedata, &gamedata->texture_pack, fd);
	parse_coin_animation(gamedata, &gamedata->coins);
	parse_map(gamedata, fd);
	close(fd);
	init_cache(gamedata->cache);
	mlx_mouse_move(gamedata->display, gamedata->window,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
}
