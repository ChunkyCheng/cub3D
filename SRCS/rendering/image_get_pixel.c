/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_get_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:59 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 17:18:33 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

int	image_get_pixel(t_image *image, int x, int y)
{
	int	*pixel;
	int	pixindx;

	if (image == NULL)
		return (RED);
	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return (RED);
	pixindx = y * image->row_len + x * image->bitsperpixel / 8;
	pixel = (int *)(image->pixels + pixindx);
	return (*pixel);
}
