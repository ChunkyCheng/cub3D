/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:25:58 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/23 23:47:59 by jchuah           ###   ########.fr       */
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

# define DARKNESS	1

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

typedef struct s_pixel_col
{
	t_image	*texture;
	double	len;
	int		col;
	double	row;
	double	row_step;
}	t_pixel_col;

typedef struct s_render_vals
{
	float	scale;
	int		x_bound;
	int		y_bound;
	int		x_offset;
	int		y_offset;
	int		scale_map_x[WIN_WIDTH];
	int		scale_map_y[WIN_HEIGHT];
}	t_render_vals;

typedef struct s_rgb
{
	float	red;
	float	green;
	float	blue;
}	t_rgb;

typedef struct s_hsv
{
	float	hue;
	float	saturation;
	float	value;
}	t_hsv;

void	render_frame(t_gamedata *gamedata, t_player *player);
void	render_background(t_image *img_buff, t_texture_pack *texture_pack);
void	init_ray(t_ray *ray, t_player *player, int col);
void	cast_ray(t_gamedata *gamedata, t_ray *ray, t_player *player);
void	render_column(t_gamedata *gamedata, t_ray *ray, int screen_col);
void	image_put_pixel(t_image *image, int x, int y, int colour);
int		image_get_pixel(t_image *image, int x, int y);
int		darken_pixel(int pixel, double scale);

void	limit_framerate(void);

#endif
