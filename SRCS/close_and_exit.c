/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:36 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/02 01:56:48 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_and_exit(t_gamedata *gamedata)
{
	int	exit_code;

	if (!gamedata->image->mlx_image || !gamedata->window || !gamedata->display)
		exit_code = 127;
	else
		exit_code = 0;
	if (gamedata->image->mlx_image)
		mlx_destroy_image(gamedata->display, gamedata->image->mlx_image);
	if (gamedata->window)
		mlx_destroy_window(gamedata->display, gamedata->window);
	if (gamedata->display)
	{
		mlx_destroy_display(gamedata->display);
		free(gamedata->display);
	}
	exit(exit_code);
}
