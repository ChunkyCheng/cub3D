/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:12:36 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/16 09:37:12 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"
#include "rendering.h"

int	game_loop(t_gamedata *gamedata)
{
	check_inputs(gamedata, gamedata->inputs, &gamedata->player);
	render_frame(gamedata, &gamedata->player);
	return (0);
}
