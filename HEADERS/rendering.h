/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 13:25:58 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/11 17:48:34 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# define FOV			90.0
# define DFL_FLOOR		0xDC6400
# define DFL_CEILING	0xFF1E00

typedef struct s_ray
{
	float	x;
	float	y;
	float	angle;
}	t_ray;

#endif
