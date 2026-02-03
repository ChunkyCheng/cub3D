/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_put_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:59 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/31 20:02:19 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

void	image_put_pixel(t_image *image, int x, int y, int colour)
{
	int	*pixel;
	int	pixindx;

	if ((colour & ALPHA) == ALPHA
		|| x < 0 || y < 0 || x >= image->width || y >= image->height)
		return ;
	pixindx = y * image->row_len + x * image->bitsperpixel / 8;
	pixel = (int *)(image->pixels + pixindx);
	*pixel = colour;
}
