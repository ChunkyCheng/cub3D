/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_coin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:42:32 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/04 16:34:09 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_coin(t_gamedata *gamedata, t_parsing *p_data, int x, int y)
{
	if (gamedata->coins.coin_total >= COIN_MAX)
		clean_error(p_data, gamedata, "Too many coins");
	gamedata->coins.pos[gamedata->coins.coin_total]
		= (t_vect){.x = x + 0.5, .y = y + 0.5};
	gamedata->coins.coin_total++;
}
