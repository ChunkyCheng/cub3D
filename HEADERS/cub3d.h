/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:26:42 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/19 17:59:05 by jchuah           ###   ########.fr       */
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

# define DEBUG			1

# define WIN_WIDTH		960
# define WIN_HEIGHT		540
# define IMG_WIDTH		768
# define IMG_HEIGHT		480
# define MAP_SIZE_MAX	128

# define PLAYER_RADIUS	0.4
# define QUANTIZE_STEP	0.01

typedef struct s_vect
{
	double	x;
	double	y;
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
	t_vect		pos;
	float		angle;
	t_vect		dir;
	t_vect		view_plane;
	double		view_plane_len;
	double		projection_dist;
	double		fov;
}	t_player;

typedef struct s_inputs			t_inputs;
typedef struct s_render_vals	t_render_vals;

typedef struct s_gamedata
{
	void			*display;
	void			*window;
	t_image			img_main;
	t_image			img_buff;
	t_texture_pack	texture_pack;
	t_map_cell		map[MAP_SIZE_MAX][MAP_SIZE_MAX];
	t_player		player;
	t_inputs		*inputs;
	t_render_vals	*render_vals;
	int				exit_code;
}	t_gamedata;

void		init_render_vals(t_render_vals *render_vals);
void		init_gamedata(t_gamedata *gamedata, char *map_path);
int			game_loop(t_gamedata *gamedata);
int			close_and_exit(t_gamedata *gamedata);
void		close_with_exit_code(t_gamedata *gamedata, int exit_code);

#endif
