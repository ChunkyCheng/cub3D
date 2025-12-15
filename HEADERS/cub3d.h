/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:26:42 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 17:45:33 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define WIN_WIDTH		1920
# define WIN_HEIGHT		1080
# define MAP_SIZE_MAX	128

typedef struct s_vect
{
	float	x;
	float	y;
}	t_vect;

typedef struct s_image
{
	void	*mlx_img;
	char	*pixels;
	int		bitsperpixel;
	int		row_len;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_texture
{
	t_image	north;
	t_image	south;
	t_image	west;
	t_image	east;
}	t_texture;

typedef struct s_texture_pack
{
	int			floor;
	int			ceiling;
	t_texture	wall1;
}	t_texture_pack;

typedef struct s_map_cell
{
	enum
	{
		EMPTY,
		WALL,
		DOOR
	}			e_type;
	t_texture	*texture;
}	t_map_cell;

typedef struct s_player
{
	t_vect	pos;
	float	angle;
	t_vect	dir;
	t_vect	view_plane;
	float	view_plane_len;
	float	projection_dist;
	float	fov;
}	t_player;

typedef struct s_inputs
{
	int	move_flags;
	int	rot_flags;
	int	mouse_x;
	int	mouse_y;
}	t_inputs;

typedef struct s_gamedata
{
	void			*display;
	void			*window;
	t_image			img_main;
	t_texture_pack	texture_pack;
	t_map_cell		map[MAP_SIZE_MAX][MAP_SIZE_MAX];
	t_player		player;
	t_inputs		inputs;
	int				exit_code;
}	t_gamedata;

void	init_gamedata(t_gamedata *gamedata, char *map_path);
int		game_loop(t_gamedata *gamedata);
int		close_and_exit(t_gamedata *gamedata);
void	close_with_exit_code(t_gamedata *gamedata, int exit_code);

#endif
