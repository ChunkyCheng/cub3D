/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 23:38:32 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/23 23:56:32 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

void	render_background(t_image *img_buff, t_texture_pack *texture_pack)
{
	int		x;
	int		y;
	float	darkness;

	y = 0;
	while (y < IMG_HEIGHT / 2)
	{
		darkness = 100 / (100.0 + y);
		x = 0;
		while (x < IMG_WIDTH)
		{
			image_put_pixel(img_buff, x, y,
				darken_pixel(texture_pack->ceiling, darkness));
			image_put_pixel(img_buff, x, IMG_HEIGHT - 1 - y,
				darken_pixel(texture_pack->floor, darkness));
			x++;
		}
		y++;
	}
}
