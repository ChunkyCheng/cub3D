/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_focus_event.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:55:15 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/16 12:41:33 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

int	handle_focus_in(t_gamedata *gamedata)
{
	gamedata->inputs->focused = 1;
	return (0);
}

int	handle_focus_out(t_gamedata *gamedata)
{
	gamedata->inputs->focused = 0;
	return (0);
}
