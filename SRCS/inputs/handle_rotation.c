/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:31:16 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 17:41:47 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

void	handle_rotation(t_inputs *inputs, t_player *player)
{
	if (inputs->rot_flags == LEFT_HOLD)
		player->angle -= ROT_SPEED;
	else if (inputs->rot_flags == RIGHT_HOLD)
		player->angle += ROT_SPEED;
	else
		return ;
	if (player->angle < 0)
		player->angle += 360;
	else if (player->angle >= 360)
		player->angle -= 360;
	player->dir.x = cos(player->angle * M_PI / 180);
	player->dir.y = sin(player->angle * M_PI / 180);
}
