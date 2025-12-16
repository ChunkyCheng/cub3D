/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:36 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/16 14:09:24 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

static void	free_texture(t_gamedata *gamedata, t_texture *texture)
{
	if (texture->north.mlx_img)
		mlx_destroy_image(gamedata->display, texture->north.mlx_img);
	if (texture->south.mlx_img)
		mlx_destroy_image(gamedata->display, texture->south.mlx_img);
	if (texture->west.mlx_img)
		mlx_destroy_image(gamedata->display, texture->west.mlx_img);
	if (texture->east.mlx_img)
		mlx_destroy_image(gamedata->display, texture->east.mlx_img);
}

static void	free_texture_pack(t_gamedata *gamedata,
t_texture_pack *texture_pack)
{
	free_texture(gamedata, &texture_pack->wall1);
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
