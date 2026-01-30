/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 15:30:00 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/31 00:45:59 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

//defines a radius as a fraction of the image size
# define MINIMAP_SIZE	0.1

//defines how many walls should fit in the diameter of the minimap 
# define MINIMAP_MAP_RADIUS	10.0

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

typedef struct s_minimap
{
	int			pix_size;
	int			wall_size;
	int			screen_x;
	int			screen_y;
	int			wall_offset_x;
	int			wall_offset_y;
	t_circle	outline;
}	t_minimap;

void	init_minimap(t_gamedata *gamedata, t_minimap *minimap);

void	draw_circle(t_image *dst, t_circle *circle);
void	draw_rectangle(t_image *dst, t_rectangle *rectangle);
void	render_minimap(t_gamedata *gamedata, t_player *player, t_minimap *minimap);

#endif
