/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_coins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:49:29 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 22:44:10 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static void	set_coin_pos_from_screen(t_player *player, t_vect coin_pos,
float *depth, int *screen_x)
{
	t_vect	coin_relpos;
	float	sideways;

	coin_relpos.x = coin_pos.x - player->pos.x;
	coin_relpos.y = coin_pos.y - player->pos.y;
	*depth = coin_relpos.x * player->dir.x + coin_relpos.y * player->dir.y;
	if (*depth <= 0)
		return ;
	sideways = (coin_relpos.x * player->view_plane.x
		+ coin_relpos.y * player->view_plane.y) / *depth;
	*screen_x = (sideways + 1) * (IMG_WIDTH - 1) / 2;
}

static void	place_coin(t_gamedata *gamedata, t_image *coin_img,
float depth, int screen_x)
{
	int	pix_width;
	int	pix_height;
	int	x;
	int	y;
	int	pixel;


	pix_width = COIN_SIZE * gamedata->render_vals->projection_dist / depth;
	pix_height = coin_img->height * pix_width / coin_img->width;
	
	float darkness = (2.0 / (gamedata->render_vals->min_wall_height - IMG_HEIGHT))
		* (IMG_HEIGHT - (pix_height * 2)) / 2 + 1.0;
	y = 0;
	while (y < pix_height)
	{
		x = 0;
		while (x < pix_width)
		{
			pixel = image_get_pixel(coin_img, coin_img->width * x / pix_width,
				coin_img->height * y / pix_height);
			if ((pixel & ALPHA) != ALPHA)
			{
				pixel = darken_pixel(pixel, darkness);
				image_put_pixel(&gamedata->img_buff, (x - pix_width / 2) + screen_x,
					(y + (IMG_HEIGHT - pix_height) / 2), pixel);
			}
			x++;
		}
		y++;
	}
}

void	render_coins(t_gamedata *gamedata, t_player *player, t_coins *coins)
{
	float	depth;
	int		screen_x;
	int		i;

	i = 0;
	while (i < coins->coin_total)
	{
		set_coin_pos_from_screen(player, coins->pos[i], &depth, &screen_x);
		if (depth > 0 && depth < player->view_dist
			&& screen_x >= 0 && screen_x < IMG_WIDTH)
			place_coin(gamedata, &coins->frames[coins->frame_current],
				depth, screen_x);
		i++;
	}
}
