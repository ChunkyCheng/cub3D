/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:25:58 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/13 20:26:35 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

# define DFL_FLOOR		0xDC6400
# define DFL_CEILING	0xFF1E00

typedef struct s_ray
{
	t_vect	pos;
	t_vect	dir;
	t_vect	step;
	t_vect	delta_dist;
	t_vect	side_dist;
	float	len;
	enum
	{
		VERTICAL,
		HORIZONTAL,
		ANGLED
	}		e_type;
	enum
	{
		X_SIDE,
		Y_SIDE
	}		e_side;
}	t_ray;

void	render_frame(t_gamedata *gamedata, t_player *player);
void	cast_ray(t_gamedata *gamedata, t_ray *ray, t_player *player);

#endif
