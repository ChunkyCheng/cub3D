/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_blend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:25:10 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/03 17:10:04 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

int	pixel_blend(int pix1, int pix2, float scale)
{
	t_rgb	colour1;
	t_rgb	out;
	int		scale_fp;

	if (scale <= 0)
		return (pix1);
	if (scale >= 1)
		return (pix2);
	scale_fp = scale * (1 << 16);
	colour1.r = (pix1 & RED) >> 16;
	colour1.g = (pix1 & GREEN) >> 8;
	colour1.b = pix1 & BLUE;
	out.r = ((((pix2 & RED) >> 16) - colour1.r) * scale_fp) >> 16;
	out.g = ((((pix2 & GREEN) >> 8) - colour1.g) * scale_fp) >> 16;
	out.b = (((pix2 & BLUE) - colour1.b) * scale_fp) >> 16;
	out.r += colour1.r;
	out.g += colour1.g;
	out.b += colour1.b;
	return ((out.r << 16) | (out.g << 8) | out.b);
}
