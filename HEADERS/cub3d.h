/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:26:42 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/03 17:56:29 by jchuah           ###   ########.fr       */
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
# include <fcntl.h>

# define DEBUG			1

//3840x2160
//1920x1080
//960x540
//768x480
# define WIN_WIDTH		3840
# define WIN_HEIGHT		2160
# define IMG_WIDTH		640
# define IMG_HEIGHT		480

# define MAP_SIZE_MAX			128
# define ANIMATION_FRAME_MAX	30
# define COIN_MAX				128

# define PLAYER_RADIUS	0.2

typedef struct s_map
{
	char	**content;
	int		**mask;
	int		height;
	int		width;
}	t_map;

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
	char	*file_path;
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
	t_image		texture[10][4];
	t_image		coin_frames[ANIMATION_FRAME_MAX];
}	t_texture_pack;

typedef struct s_map_cell
{
	enum
	{
		EMPTY,
		WALL,
		DOOR,
		UNBOUND
	}		e_type;
	int		solid;
	int		visible;
	t_image	*north;
	t_image	*south;
	t_image	*west;
	t_image	*east;
}	t_map_cell;

typedef struct s_player
{
	t_vect		pos;
	float		angle;
	t_vect		dir;
	t_vect		view_plane;
	double		fov;
	double		view_dist;
}	t_player;

typedef struct s_coins
{
	t_vect	pos[COIN_MAX];
	t_image	(*frames)[30];
	int		coin_total;
	int		frame_total;
	int		frame_current;
	int		frame_delay;
}	t_coins;

typedef struct s_minimap	t_minimap;
typedef struct s_inputs		t_inputs;
typedef struct s_cache		t_cache;

typedef struct s_gamedata
{
	void			*display;
	void			*window;
	t_image			img_main;
	t_image			img_buff;
	t_minimap		*minimap;
	t_texture_pack	texture_pack;
	t_map			pmap;
	t_map_cell		map[MAP_SIZE_MAX][MAP_SIZE_MAX];
	t_player		player;
	t_coins			coins;
	t_inputs		*inputs;
	t_cache			*cache;
	int				exit_code;
}	t_gamedata;

void		init_cache(t_gamedata *gamedata, t_cache *cache);
void		parsing(t_gamedata *gamedata, char *map_path);
void		init_gamedata(t_gamedata *gamedata);
int			game_loop(t_gamedata *gamedata);
void		free_mask(int **arr, int height);
int			close_and_exit(t_gamedata *gamedata);
void		close_with_exit_code(t_gamedata *gamedata, int exit_code);

#endif
