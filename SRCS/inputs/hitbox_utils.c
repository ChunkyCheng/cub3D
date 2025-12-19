/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 16:34:54 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/18 18:58:55 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

#define COLLISION_DEBUG 0

static void	print_hitbox(char *label, t_hitbox *hitbox)
{
	printf("%s\ntopleft:  %.18f %.18f\nbotright: %.18f %.18f\n", label,
		hitbox->topleft.x, hitbox->topleft.y,
		hitbox->botright.x, hitbox->botright.y);
}

t_hitbox	player_hitbox(t_vect pos)
{
	t_hitbox	hitbox;

	hitbox.topleft.x = pos.x - PLAYER_RADIUS;
	hitbox.topleft.y = pos.y - PLAYER_RADIUS;
	hitbox.botright.x = pos.x + PLAYER_RADIUS;
	hitbox.botright.y = pos.y + PLAYER_RADIUS;
	return (hitbox);
}

t_hitbox	cell_hitbox(int x, int y)
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
	if (COLLISION_DEBUG)
	{
		print_hitbox("hitbox1", &hitbox1);
		print_hitbox("hitbox2", &hitbox2);
	}
	if (hitbox1.topleft.x < hitbox2.botright.x
		&& hitbox1.botright.x > hitbox2.topleft.x
		&& hitbox1.topleft.y < hitbox2.botright.y
		&& hitbox1.botright.y > hitbox2.topleft.y)
	{
		if (COLLISION_DEBUG)
			printf("collision true\n\n");
		return (1);
	}
	if (COLLISION_DEBUG)
		printf("collision false\n\n");
	return (0);
}
