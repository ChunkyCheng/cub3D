/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render_vals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:53:30 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/16 15:02:47 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

void	init_render_vals(t_render_vals *render_vals)
{
	if (WIN_HEIGHT < WIN_WIDTH)
	{
		render_vals->scale = IMG_HEIGHT / (float)WIN_HEIGHT;
		render_vals->x_offset
			= (WIN_WIDTH - (IMG_WIDTH / render_vals->scale)) / 2;
		render_vals->y_offset = 0;
	}
	else
	{
		render_vals->scale = IMG_WIDTH / (float)WIN_WIDTH;
		render_vals->x_offset = 0;
		render_vals->y_offset
			= (WIN_HEIGHT - (IMG_HEIGHT / render_vals->scale)) / 2;
	}
}
