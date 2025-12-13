/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:12:36 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/13 20:26:53 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

int	game_loop(t_gamedata *gamedata)
{
	render_frame(gamedata, &gamedata->player);
	close_and_exit(gamedata);
	return (0);
}
