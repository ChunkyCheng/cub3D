/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:25:58 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/03 17:08:41 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# define FRAMERATE	30
# include "cub3d.h"

# define ALPHA	0xFF000000
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define BLACK	0x00000000

# define DFL_VIEW_DIST	7.0
# define DFL_FOV		90

# define COIN_SIZE		0.5

typedef struct s_ray
{
	int		norm_x;
	int		norm_y;
	t_vect	dir;
	t_vect	step;
	t_vect	delta_dist;
	t_vect	side_dist;
	double	len;
	enum
	{
		ANGLED,
		VERTICAL,
		HORIZONTAL
	}		e_type;
	enum
	{
		X_SIDE,
		Y_SIDE
	}		e_side;
	int		out_of_bounds;
}	t_ray;

typedef struct s_pix_col
{
	t_image	*texture;
	int		full_height;
	int		tex_x;
	int		screen_x;
	double	tex_y_top;
	double	tex_step;
	int		screen_y_top;
	int		draw_height;
}	t_pix_col;

typedef struct s_screen_pos
{
	float	depth;
	int		screen_x;
}	t_screen_pos;

typedef struct s_upscaling
{
	float	scale;
	int		x_bound;
	int		y_bound;
	int		x_offset;
	int		y_offset;
	int		needs_scaling;
	int		scale_map_x[WIN_WIDTH];
	int		scale_map_y[WIN_HEIGHT];
}	t_upscaling;

typedef struct s_cache
{
	double		view_plane_len;
	double		projection_dist;
	int			min_wall_height;
	float		z_buffer[IMG_WIDTH];
	int			fog_colour;
	t_upscaling	upscaling;
}	t_cache;

typedef struct t_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

void	render_frame(t_gamedata *gamedata, t_cache *cache,
			t_player *player);
void	render_background(t_gamedata *gamedata, t_texture_pack *texture_pack,
			t_cache *cache);
void	init_ray(t_ray *ray, t_player *player, int col);
void	cast_ray(t_gamedata *gamedata, t_ray *ray, t_player *player);
void	render_wall_column(t_gamedata *gamedata, t_ray *ray, int screen_col);
void	render_coins(t_gamedata *gamedata, t_player *player, t_coins *coins);
void	push_image(t_gamedata *gamedata);

void	update_animations(t_gamedata *gamedata);

void	image_put_pixel(t_image *image, int x, int y, int colour);
int		image_get_pixel(t_image *image, int x, int y);
int		darken_pixel(int pixel, float scale);
int		pixel_blend(int pix1, int pix2, float scale);

void	init_pix_col(t_pix_col *pix_col);
void	draw_pix_col(t_image *dst, t_pix_col *pix_col, int fog,
			float fog_scale);

void	limit_framerate(void);

#endif
