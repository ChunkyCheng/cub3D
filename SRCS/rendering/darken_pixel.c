/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darken_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 19:34:14 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/26 12:05:56 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static int	rgb_prime_to_pixel(t_rgb rgb_prime)
{
	int	red;
	int	green;
	int	blue;

	red = ((int)(rgb_prime.red * 255)) << 16;
	green = ((int)(rgb_prime.green * 255)) << 8;
	blue = (int)(rgb_prime.blue * 255);
	return (red | green | blue);
}

static int	hsv_to_pixel(t_hsv hsv)
{
	t_rgb	rgb_prime;
	float	chroma;
	float	mid;
	float	match;

	chroma = hsv.saturation * hsv.value;
	mid = chroma * (1 - fabs(fmod(hsv.hue / 60, 2) - 1));
	match = hsv.value - chroma;
	if (hsv.hue < 60)
		rgb_prime = (t_rgb){.red = chroma, .green = mid, .blue = 0};
	else if (hsv.hue < 120)
		rgb_prime = (t_rgb){.red = mid, .green = chroma, .blue = 0};
	else if (hsv.hue < 180)
		rgb_prime = (t_rgb){.red = 0, .green = chroma, .blue = mid};
	else if (hsv.hue < 240)
		rgb_prime = (t_rgb){.red = 0, .green = mid, .blue = chroma};
	else if (hsv.hue < 300)
		rgb_prime = (t_rgb){.red = mid, .green = 0, .blue = chroma};
	else
		rgb_prime = (t_rgb){.red = chroma, .green = 0, .blue = mid};
	rgb_prime.red += match;
	rgb_prime.green += match;
	rgb_prime.blue += match;
	return (rgb_prime_to_pixel(rgb_prime));
}

static float	get_hue(t_rgb rgb_prime, float min, float max)
{
	float	hue;

	if (max == min)
		return (0);
	else if (max == rgb_prime.red)
		hue = fmod((rgb_prime.green - rgb_prime.blue) / (max - min), 6);
	else if (max == rgb_prime.green)
		hue = (rgb_prime.blue - rgb_prime.red) / (max - min) + 2;
	else
		hue = (rgb_prime.red - rgb_prime.green) / (max - min) + 4;
	hue *= 60;
	if (hue < 0)
		hue += 360;
	return (hue);
}

static t_hsv	pixel_to_hsv(int pixel)
{
	t_rgb	rgb_prime;
	t_hsv	hsv;
	float	min;
	float	max;

	rgb_prime.red = ((pixel & RED) >> 16) / 255.0;
	rgb_prime.green = ((pixel & GREEN) >> 8) / 255.0;
	rgb_prime.blue = (pixel & BLUE) / 255.0;
	min = fmin(rgb_prime.red, rgb_prime.green);
	min = fmin(min, rgb_prime.blue);
	max = fmax(rgb_prime.red, rgb_prime.green);
	max = fmax(max, rgb_prime.blue);
	hsv.hue = get_hue(rgb_prime, min, max);
	if (max == 0)
		hsv.saturation = 0;
	else
		hsv.saturation = (max - min) / max;
	hsv.value = max;
	return (hsv);
}

int	darken_pixel(int pixel, double scale)
{
	t_hsv	hsv;
	t_uchar	alpha;

	alpha = pixel & ALPHA;
	pixel = pixel & ~ALPHA;
	hsv = pixel_to_hsv(pixel);
	hsv.value *= scale;
	if (hsv.value < 0.01)
		hsv.value = 0;
	if (hsv.value > 1)
		hsv.value = 1;
	return (hsv_to_pixel(hsv) | alpha);
}
