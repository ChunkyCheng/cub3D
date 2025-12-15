/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 09:17:22 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 09:43:29 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parsing.h"

void	init_image_data(t_image *image)
{
	if (!image->mlx_img)
		printf("VOIDDD\n");
	image->pixels = mlx_get_data_addr(image->mlx_img, &image->bitsperpixel,
			&image->row_len, &image->endian);
}
