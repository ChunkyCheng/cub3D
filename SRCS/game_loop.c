/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:12:36 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 16:55:33 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"
#include "rendering.h"

int	game_loop(t_gamedata *gamedata)
{
	check_inputs(gamedata, gamedata->inputs, &gamedata->player);
	render_frame(gamedata, gamedata->render_vals, &gamedata->player);
	return (0);
}
