/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:18:21 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/02 17:25:27 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_image_data(t_image *image, t_gamedata *gamedata)
{
	image->mlx_img
		= mlx_xpm_file_to_image(gamedata->display,
			image->file_path,
			&image->width,
			&image->height);
	if (!image->mlx_img)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putendl_fd(image->file_path, 2);
		close_with_exit_code(gamedata, 127);
	}
	image->pixels = mlx_get_data_addr(image->mlx_img, &image->bitsperpixel,
			&image->row_len, &image->endian);
	if (!image->pixels)
	{
		ft_putstr_fd("Error\nFailed to get image data address", 2);
		close_with_exit_code(gamedata, 127);
	}
}
