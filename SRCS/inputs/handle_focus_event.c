/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_focus_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:55:15 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 11:45:37 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

int	handle_focus_in(t_gamedata *gamedata)
{
	gamedata->inputs->focused = 1;
	return (0);
}

int	handle_focus_out(t_gamedata *gamedata)
{
	t_inputs	*inputs;

	inputs = gamedata->inputs;
	inputs->focused = 0;
	inputs->move_flags = 0;
	inputs->rot_flags = 0;
	inputs->x_move = 0;
	inputs->y_move = 0;
	return (0);
}
