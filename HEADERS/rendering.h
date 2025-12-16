/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:25:58 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/16 16:07:46 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# define FRAMERATE	60
# include "cub3d.h"

typedef struct s_ray
{
	int		norm_x;
	int		norm_y;
	t_vect	dir;
	t_vect	step;
	t_vect	delta_dist;
	t_vect	side_dist;
	float	len;
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
	int		len;
	int		col;
	float	row;
	float	row_step;
}	t_pixel_col;

typedef struct s_render_vals
{
	float	scale;
	int		x_offset;
	int		y_offset;
}	t_render_vals;

void	render_frame(t_gamedata *gamedata, t_player *player);
void	init_ray(t_ray *ray, t_player *player, int col);
void	cast_ray(t_gamedata *gamedata, t_ray *ray, t_player *player);
void	render_column(t_gamedata *gamedata, t_ray *ray, int screen_col);
void	image_put_pixel(t_image *image, int x, int y, int colour);
int		image_get_pixel(t_image *image, int x, int y);

void	limit_framerate(void);

#endif
