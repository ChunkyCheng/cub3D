/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pix_col.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:19:05 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/02 23:09:34 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

//only use once texture and full_height are set
void	init_pix_col(t_pix_col *pix_col)
{
	pix_col->tex_step = (double)pix_col->texture->height / pix_col->full_height;
	if (pix_col->full_height > IMG_HEIGHT)
	{
		pix_col->tex_y_top
			= (pix_col->full_height - IMG_HEIGHT) * pix_col->tex_step / 2.0;
		pix_col->screen_y_top = 0;
		pix_col->draw_height = IMG_HEIGHT;
	}
	else
	{
		pix_col->tex_y_top = 0;
		pix_col->screen_y_top = (IMG_HEIGHT - pix_col->full_height) / 2;
		pix_col->draw_height = (int)pix_col->full_height;
	}
}
