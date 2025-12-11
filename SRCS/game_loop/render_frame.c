/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jchuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:22:53 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/11 20:05:47 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

void	cast_ray(t_gamedata *gamedata, t_ray *ray, int col)
{
		

}

void render_frame(t_gamedata *gamedata)
{
	t_ray	ray;
	int		col;

	ray.x = gamedata->player.x;
	ray.y = gamedata->player.y;
	col = 0;
	while (col < WIN_WIDTH)
	{
		ray.angle = gamedata->player.angle;
		ray.angle += (i - WIN_WIDTH / 2.0) * (FOV / WIN_WIDTH);
		if (ray.angle < 0)
			ray.angle = 360 - ray.angle;
		if (ray.angle > 360
		cast_ray(gamedata, &ray, col)
		col++;
	}
	mlx_put_image_to_window(gamedata->display, gamedata->window,
		gamedata->img_main.mlx_img, 0, 0);
}
