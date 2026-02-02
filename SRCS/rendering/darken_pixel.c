/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darken_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:34:14 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/02 20:46:28 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

int	darken_pixel(int pixel, float scale)
{
	int	a;
	int	r;
	int	g;
	int	b;

	if (scale < 0)
		return (0);
	if (scale >= 1)
		return (pixel);
	a = pixel & ALPHA;
	r = ((pixel & RED) >> 16) * scale;
	g = ((pixel & GREEN) >> 8) * scale;
	b = (pixel & BLUE) * scale;
	return (a | (r << 16) | (g << 8) | b);
}
