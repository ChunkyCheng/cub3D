/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:36 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 17:31:15 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

static void	free_image(t_gamedata *gamedata, t_image *image)
{
	if (image->file_path)
		free(image->file_path);
	if (image->mlx_img && gamedata && gamedata->display)
		mlx_destroy_image(gamedata->display, image->mlx_img);
	image->file_path = NULL;
	image->mlx_img = NULL;
}

static void	free_texture_pack(t_gamedata *gamedata,
t_texture_pack *texture_pack)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 4)
		{
			free_image(gamedata, &texture_pack->wall[i][j]);
			j++;
		}
		i++;
	}
}

int	close_and_exit(t_gamedata *gamedata)
{
	free_texture_pack(gamedata, &gamedata->texture_pack);
	if (gamedata->img_buff.mlx_img)
		mlx_destroy_image(gamedata->display, gamedata->img_buff.mlx_img);
	if (gamedata->img_main.mlx_img)
		mlx_destroy_image(gamedata->display, gamedata->img_main.mlx_img);
	if (gamedata->window)
		mlx_destroy_window(gamedata->display, gamedata->window);
	if (gamedata->display)
	{
		mlx_destroy_display(gamedata->display);
		free(gamedata->display);
	}
	exit(gamedata->exit_code);
}

void	close_with_exit_code(t_gamedata *gamedata, int exit_code)
{
	gamedata->exit_code = exit_code;
	close_and_exit(gamedata);
}
