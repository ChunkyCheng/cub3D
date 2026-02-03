/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coin_animation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 01:51:14 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/03 22:54:08 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "cub3d.h"
#include "parsing.h"
#include "rendering.h"

void	init_coin_animation(t_gamedata *gamedata, t_texture_pack *texture_pack,
t_coins *coins)
{
	(void)gamedata;
	texture_pack->coin_frames[4] = texture_pack->coin_frames[0];
	texture_pack->coin_frames[5] = texture_pack->coin_frames[0];
	texture_pack->coin_frames[6] = texture_pack->coin_frames[0];
	texture_pack->coin_frames[7] = texture_pack->coin_frames[0];
	coins->frames = &texture_pack->coin_frames;
	coins->frame_total = 8;
	coins->frame_current = 0;
	coins->frame_delay = 5;
}
