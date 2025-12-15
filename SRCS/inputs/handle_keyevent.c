/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyevent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 02:34:23 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 17:40:42 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

int	handle_keypress(int key, t_gamedata *gamedata)
{
	if (key == XK_w)
		gamedata->inputs.move_flags |= W_HOLD;
	else if (key == XK_a)
		gamedata->inputs.move_flags |= A_HOLD;
	else if (key == XK_s)
		gamedata->inputs.move_flags |= S_HOLD;
	else if (key == XK_d)
		gamedata->inputs.move_flags |= D_HOLD;
	else if (key == XK_Left)
		gamedata->inputs.rot_flags |= LEFT_HOLD;
	else if (key == XK_Right)
		gamedata->inputs.rot_flags |= RIGHT_HOLD;
	return (0);
}

int	handle_keyrelease(int key, t_gamedata *gamedata)
{
	if (key == XK_Escape)
		close_and_exit(gamedata);
	if (key == XK_w)
		gamedata->inputs.move_flags &= ~W_HOLD;
	else if (key == XK_a)
		gamedata->inputs.move_flags &= ~A_HOLD;
	else if (key == XK_s)
		gamedata->inputs.move_flags &= ~S_HOLD;
	else if (key == XK_d)
		gamedata->inputs.move_flags &= ~D_HOLD;
	else if (key == XK_Left)
		gamedata->inputs.rot_flags &= ~LEFT_HOLD;
	else if (key == XK_Right)
		gamedata->inputs.rot_flags &= ~RIGHT_HOLD;
	return (0);
}
