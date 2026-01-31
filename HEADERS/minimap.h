/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:30:00 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/31 22:40:42 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

//defines a radius as a fraction of the image size
# define MINIMAP_SIZE	0.2

//defines how many walls should fit in the diameter of the minimap 
# define MINIMAP_MAP_RADIUS	10

typedef struct s_line_x
{
	int	x_start;
	int	x_end;
	int	y;
	int	colour;
}	t_line_x;

typedef struct s_int_vect
{
	int	x;
	int	y;
}	t_int_vect;

typedef struct s_circle
{
	int	mid_x;
	int	mid_y;
	int	radius;
	int colour;
}	t_circle;

typedef struct s_rectangle
{
	int	top_x;
	int	top_y;
	int	bot_x;
	int	bot_y;
	int	colour;
}	t_rectangle;

typedef struct s_triangle
{
	t_int_vect	p0;
	t_int_vect	p1;
	t_int_vect	p2;
	int			colour;
}	t_triangle;

typedef struct s_minimap
{
	int			pix_size;
	int			wall_size;
	int			screen_x;
	int			screen_y;
	int			wall_offset_x;
	int			wall_offset_y;
	t_circle	outline;
	t_triangle	player;
	int			visible;
}	t_minimap;

void	init_minimap(t_gamedata *gamedata, t_minimap *minimap);

void		draw_circle(t_image *dst, t_circle *circle);
void		draw_rectangle(t_image *dst, t_rectangle *rect);
void		draw_rectangle_masked(t_image *dst, t_rectangle *rect, t_circle *mask);
void		draw_triangle(t_image *dst, t_triangle *triangle);
t_triangle	rotate_minimap_player(t_minimap *minimap, t_player *player);

void	render_minimap(t_gamedata *gamedata, t_player *player, t_minimap *minimap);

#endif
