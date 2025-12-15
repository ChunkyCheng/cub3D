/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 16:54:11 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/15 17:41:11 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

void	check_inputs(t_gamedata *gamedata, t_inputs *inputs,
t_player *player)
{
	(void)gamedata;
	handle_movement(inputs, player);
	handle_rotation(inputs, player);
}
