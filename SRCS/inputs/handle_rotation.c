/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:31:16 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 11:45:37 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

void	handle_rotation(t_inputs *inputs, t_player *player)
{
	if (inputs->x_move)
		player->angle += inputs->x_move * ROT_SPEED_MOUSE;
	else if (inputs->rot_flags == LEFT_HOLD)
		player->angle -= ROT_SPEED_KEY;
	else if (inputs->rot_flags == RIGHT_HOLD)
		player->angle += ROT_SPEED_KEY;
	else
		return ;
	if (player->angle < 0)
		player->angle += 360;
	else if (player->angle >= 360)
		player->angle -= 360;
	player->dir.x = cos(player->angle * M_PI / 180);
	player->dir.y = sin(player->angle * M_PI / 180);
}
