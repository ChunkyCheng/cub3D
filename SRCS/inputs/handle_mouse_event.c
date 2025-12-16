/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 08:30:39 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/16 09:58:22 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

int	handle_mouse_press(int button, int x, int y, t_gamedata *gamedata)
{
	(void)x;
	(void)y;
	if (button == 1)
		gamedata->inputs->click_flags |= LCLICK_HOLD;
	return (0);
}

int	handle_mouse_release(int button, int x, int y, t_gamedata *gamedata)
{
	(void)x;
	(void)y;
	if (button == 1)
		gamedata->inputs->click_flags &= ~LCLICK_HOLD;
	return (0);
}

int	handle_mouse_move(int x, int y, t_gamedata *gamedata)
{
	t_inputs	*inputs;

	inputs = gamedata->inputs;
	inputs->x_move = x - inputs->mouse_x;
	inputs->y_move = y - inputs->mouse_y;
	inputs->mouse_x = x;
	inputs->mouse_y = y;
	return (0);
}
