/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_minimap_toggle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 17:11:07 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/31 22:47:18 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"
#include "minimap.h"

void	handle_minimap_toggle(t_inputs *inputs, t_minimap *minimap)
{
	static int	use_hold;

	if ((inputs->move_flags & M_HOLD) && (!use_hold))
	{
		use_hold = 1;
		minimap->visible = !minimap->visible;
	}
	if (!(inputs->move_flags & M_HOLD))
		use_hold = 0;
}
