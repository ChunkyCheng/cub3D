/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_coins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:49:29 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/29 17:09:57 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static int	compare_sprite_depth(const void *ptr1, const void *ptr2)
{
	const t_sprite_pos	*a = ptr1;
	const t_sprite_pos	*b = ptr2;

	if (a->depth < b->depth)
		return (1);
	if (b->depth < a->depth)
		return (-1);
	return (0);
}

static void	set_coin_pos_from_screen(t_player *player, t_vect coin_pos,
t_sprite_pos *sprite_pos)
{
	t_vect	coin_relpos;
	float	sideways;

	coin_relpos.x = coin_pos.x - player->pos.x;
	coin_relpos.y = coin_pos.y - player->pos.y;
	sprite_pos->depth
		= coin_relpos.x * player->dir.x + coin_relpos.y * player->dir.y;
	if (sprite_pos->depth <= 0 || sprite_pos->depth > player->view_dist)
		return ;
	sideways = (coin_relpos.x * player->view_plane.x
		+ coin_relpos.y * player->view_plane.y) / sprite_pos->depth;
	sprite_pos->screen_x = (sideways + 1) * (IMG_WIDTH - 1) / 2;
}

static void	place_coin(t_gamedata *gamedata, t_image *coin_img,
t_sprite_pos *sprite_pos)
{
	int	pix_width;
	int	pix_height;
	int	x;
	int	y;
	int	pixel;


	pix_width = COIN_SIZE * gamedata->cache->projection_dist / sprite_pos->depth;
	pix_height = coin_img->height * pix_width / coin_img->width;
	
	float darkness = (2.0 / (gamedata->cache->min_wall_height - IMG_HEIGHT))
		* (IMG_HEIGHT - (pix_height * 2)) / 2 + 1.0;
	x = 0;
	while (x < pix_width)
	{
		if (sprite_pos->depth
			< gamedata->cache->z_buffer[(x - pix_width / 2) + sprite_pos->screen_x])
		{
			y = 0;
			while (y < pix_height)
			{
				pixel = image_get_pixel(coin_img, coin_img->width * x / pix_width,
					coin_img->height * y / pix_height);
				if ((pixel & ALPHA) != ALPHA)
				{
					pixel = darken_pixel(pixel, darkness);
					image_put_pixel(&gamedata->img_buff,
						(x - pix_width / 2) + sprite_pos->screen_x,
						(y + (IMG_HEIGHT - pix_height) / 2), pixel);
				}
				y++;
			}
		}
		x++;
	}
}

void	render_coins(t_gamedata *gamedata, t_player *player, t_coins *coins)
{
	t_sprite_pos	sprite_pos[COIN_MAX];
	int				i;
	int				visible_coins;	

	i = 0;
	visible_coins = 0;
	while (i < coins->coin_total)
	{
		set_coin_pos_from_screen(player, coins->pos[i], &sprite_pos[visible_coins]);
		if (sprite_pos[visible_coins].depth > 0 && sprite_pos[visible_coins].depth < player->view_dist
			&& sprite_pos[visible_coins].screen_x >= 0 && sprite_pos[visible_coins].screen_x < IMG_WIDTH)
			visible_coins++;
		i++;
	}
	ft_qsort(sprite_pos, visible_coins, sizeof(t_sprite_pos), &compare_sprite_depth);
	i = 0;
	while (i < visible_coins)
	{
		place_coin(gamedata, &coins->frames[coins->frame_current],
				&sprite_pos[i]);
		i++;
	}
}
