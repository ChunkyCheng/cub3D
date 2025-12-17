/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:34:54 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/17 19:06:34 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

t_hitbox	player_hitbox(t_vect pos)
{
	t_hitbox	hitbox;

	hitbox.topleft.x = pos.x - PLAYER_SIZE / 2.0;
	hitbox.topleft.y = pos.y - PLAYER_SIZE / 2.0;
	hitbox.botright.x = pos.x + PLAYER_SIZE / 2.0;
	hitbox.botright.y = pos.y + PLAYER_SIZE / 2.0;
	return (hitbox);
}

t_hitbox	cell_hitbox(int	x, int y)
{
	t_hitbox	hitbox;

	hitbox.topleft.x = x;
	hitbox.topleft.y = y;
	hitbox.botright.x = x + 1;
	hitbox.botright.y = y + 1;
	return (hitbox);
}

int	is_collision(t_hitbox hitbox1, t_hitbox hitbox2)
{
	if (hitbox1.topleft.x < hitbox2.botright.x
		&& hitbox1.botright.x > hitbox2.topleft.x
		&& hitbox1.topleft.y < hitbox2.botright.y
		&& hitbox1.botright.y > hitbox2.topleft.y)
		return (1);
	return (0);
}
