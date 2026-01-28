/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_animations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:42:29 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 19:45:36 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

void	update_animations(t_gamedata *gamedata)
{
	t_coins		*coins;
	static int	coin_frame;

	coins = &gamedata->coins;
	coin_frame++;
	if (coin_frame == coins->frame_delay)
	{
		coin_frame = 0;
		coins->frame_current = (coins->frame_current + 1) % coins->frame_total;
	}
}
