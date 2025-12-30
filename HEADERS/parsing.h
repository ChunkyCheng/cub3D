/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:31:35 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/30 21:25:19 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# define DFL_FLOOR		0x393A40
# define DFL_CEILING	0x1A1C20

# define DFL_NORTH		"textures/wall-default-north.xpm"
# define DFL_SOUTH		"textures/wall-default-south.xpm"
# define DFL_WEST		"textures/wall-default-west.xpm"
# define DFL_EAST		"textures/wall-default-east.xpm"

typedef struct s_render_vals	t_render_vals;

void	init_render_vals(t_render_vals *render_vals);
void	init_image_data(t_image *image);

#endif
