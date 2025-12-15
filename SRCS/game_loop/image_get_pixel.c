/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_get_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:21:59 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 15:53:46 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	image_get_pixel(t_image *image, int x, int y)
{
	int	*pixel;
	int	pixindx;

	if (x < 0 || y < 0 || x >= image->width || y >= image->height)
		return (0);
	pixindx = y * image->row_len + x * image->bitsperpixel / 8;
	pixel = (int *)(image->pixels + pixindx);
	return (*pixel);
}
