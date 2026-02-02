/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_coin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:42:32 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/02 14:45:05 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_coin(t_coins *coins, int x, int y)
{
	coins->pos[coins->coin_total] = (t_vect){.x = x + 0.5, .y = y + 0.5};
	coins->coin_total++;
}
