/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_coins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:49:29 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 01:46:08 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"

static int	compare_sprite_depth(const void *ptr1, const void *ptr2)
{
	const t_screen_pos	*a = ptr1;
	const t_screen_pos	*b = ptr2;

	if (a->depth < b->depth)
		return (1);
	if (b->depth < a->depth)
		return (-1);
	return (0);
}

static void	set_coin_pos_from_screen(t_gamedata *gamedata, t_player *player,
t_vect coin_pos, t_screen_pos *screen_pos)
{
	t_vect	coin_relpos;
	float	sideways;

	coin_relpos.x = coin_pos.x - player->pos.x;
	coin_relpos.y = coin_pos.y - player->pos.y;
	screen_pos->depth
		= coin_relpos.x * player->dir.x + coin_relpos.y * player->dir.y;
	if (screen_pos->depth <= 0 || screen_pos->depth > player->view_dist)
		return ;
	sideways
		= (coin_relpos.x * -player->dir.y + coin_relpos.y * player->dir.x)
		/ (screen_pos->depth * gamedata->cache->view_plane_len);
	screen_pos->screen_x = (sideways + 1) * (IMG_WIDTH - 1) / 2;
}

static void	place_coin(t_gamedata *gamedata, t_image *coin_img,
float depth, int screen_x)
{
	t_pix_col	pix_col;
	float		darkness;
	int			x;

	pix_col.texture = coin_img;
	pix_col.full_height = gamedata->cache->projection_dist / depth;
	screen_x -= pix_col.full_height / 2;
	init_pix_col(&pix_col);
	darkness = (2.0 / (gamedata->cache->min_wall_height - IMG_HEIGHT))
		* pix_col.screen_y_top + 1.0;
	x = 0;
	while (x < pix_col.full_height)
	{
		if (screen_x >= 0 && screen_x < IMG_WIDTH
			&& depth < gamedata->cache->z_buffer[screen_x])
		{
			pix_col.tex_x = x * pix_col.tex_step;
			pix_col.screen_x = screen_x;
			draw_pix_col(&gamedata->img_buff, &pix_col, darkness);
		}
		screen_x++;
		x++;
	}
}

void	render_coins(t_gamedata *gamedata, t_player *player, t_coins *coins)
{
	int				i;
	int				visible;
	t_screen_pos	screen_pos[COIN_MAX];

	i = 0;
	visible = 0;
	while (i < coins->coin_total)
	{
		set_coin_pos_from_screen(gamedata, player,
			coins->pos[i], &screen_pos[visible]);
		if (screen_pos[visible].depth > 0
			&& screen_pos[visible].depth <= player->view_dist
			&& screen_pos[visible].screen_x >= 0
			&& screen_pos[visible].screen_x < IMG_WIDTH)
			visible++;
		i++;
	}
	ft_qsort(screen_pos, visible, sizeof(t_screen_pos), &compare_sprite_depth);
	i = 0;
	while (i < visible)
	{
		place_coin(gamedata, &coins->frames[coins->frame_current],
			screen_pos[i].depth, screen_pos[i].screen_x);
		i++;
	}
}
