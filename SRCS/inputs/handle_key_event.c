/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 02:34:23 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/16 10:01:14 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

int	handle_key_press(int key, t_gamedata *gamedata)
{
	t_inputs	*inputs;

	inputs = gamedata->inputs;
	if (key == XK_w)
		inputs->move_flags |= W_HOLD;
	else if (key == XK_a)
		inputs->move_flags |= A_HOLD;
	else if (key == XK_s)
		inputs->move_flags |= S_HOLD;
	else if (key == XK_d)
		inputs->move_flags |= D_HOLD;
	else if (key == XK_Left)
		inputs->rot_flags |= LEFT_HOLD;
	else if (key == XK_Right)
		inputs->rot_flags |= RIGHT_HOLD;
	return (0);
}

int	handle_key_release(int key, t_gamedata *gamedata)
{
	t_inputs	*inputs;

	inputs = gamedata->inputs;
	if (key == XK_Escape)
		close_and_exit(gamedata);
	if (key == XK_w)
		inputs->move_flags &= ~W_HOLD;
	else if (key == XK_a)
		inputs->move_flags &= ~A_HOLD;
	else if (key == XK_s)
		inputs->move_flags &= ~S_HOLD;
	else if (key == XK_d)
		inputs->move_flags &= ~D_HOLD;
	else if (key == XK_Left)
		inputs->rot_flags &= ~LEFT_HOLD;
	else if (key == XK_Right)
		inputs->rot_flags &= ~RIGHT_HOLD;
	return (0);
}
