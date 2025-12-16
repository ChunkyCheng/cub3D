/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gamedata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:51:14 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/16 15:01:34 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"
#include "parsing.h"

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
				gamedata->map[y][x].texture = &gamedata->texture_pack.wall1;
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
	parse_map(gamedata, fd);
	close(fd);
	init_render_vals(gamedata->render_vals);
}
