/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:36 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/02 17:41:52 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

void	free_mask(int **arr, int height)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < height)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_coin_animation(t_gamedata *gamedata,
t_texture_pack *texture_pack)
{
	t_image	*frame;

	frame = &texture_pack->coin_frames[0];
	if (frame->mlx_img)
		mlx_destroy_image(gamedata->display, frame->mlx_img);
	frame = &texture_pack->coin_frames[1];
	if (frame->mlx_img)
		mlx_destroy_image(gamedata->display, frame->mlx_img);
	frame = &texture_pack->coin_frames[2];
	if (frame->mlx_img)
		mlx_destroy_image(gamedata->display, frame->mlx_img);
	frame = &texture_pack->coin_frames[3];
	if (frame->mlx_img)
		mlx_destroy_image(gamedata->display, frame->mlx_img);
}

static void	free_texture_pack(t_gamedata *gamedata,
t_texture_pack *texture_pack)
{
	int		i;
	int		j;
	t_image	*image;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 4)
		{
			image = &texture_pack->texture[i][j];
			if (i != 0 && image->file_path)
				free(image->file_path);
			if (image->mlx_img && gamedata && gamedata->display)
				mlx_destroy_image(gamedata->display, image->mlx_img);
			image->file_path = NULL;
			image->mlx_img = NULL;
			j++;
		}
		i++;
	}
	free_coin_animation(gamedata, texture_pack);
}

int	close_and_exit(t_gamedata *gamedata)
{
	free_texture_pack(gamedata, &gamedata->texture_pack);
	if (gamedata->pmap.mask)
		free_mask(gamedata->pmap.mask, gamedata->pmap.height);
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
