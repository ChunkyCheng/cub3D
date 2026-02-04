/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:36 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/04 14:56:42 by lming-ha         ###   ########.fr       */
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

static void	free_image(t_gamedata *gamedata, t_image *texture)
{
	int		i;
	t_image	*image;

	i = 0;
	while (i < 4)
	{
		image = &texture[i];
		if (image->file_path)
			free(image->file_path);
		if (image->mlx_img)
			mlx_destroy_image(gamedata->display, image->mlx_img);
		image->file_path = NULL;
		image->mlx_img = NULL;
		i++;
	}
}

static void	free_textures(t_gamedata *gamedata,
t_texture_pack *texture_pack)
{
	int		i;

	i = 0;
	while (i < TEXTURES)
	{
		free_image(gamedata, texture_pack->texture[i]);
		i++;
	}
	free_image(gamedata, texture_pack->coin_frames);
}

int	close_and_exit(t_gamedata *gamedata)
{
	free_textures(gamedata, &gamedata->texture_pack);
	if (gamedata->pmap.content)
		ft_strarr_free(gamedata->pmap.content);
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
