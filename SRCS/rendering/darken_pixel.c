/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darken_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:34:14 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 12:08:14 by jchuah           ###   ########.fr       */
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

	a = pixel & ALPHA;
	r = ((pixel & RED) >> 16) * scale;
	g = ((pixel & GREEN) >> 8) * scale;
	b = (pixel & BLUE) * scale;
	return (a | (r << 16) | (g << 8) | b);
}
