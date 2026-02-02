/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:38:19 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/02 15:31:38 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"
#include "minimap.h"

static int	get_cell_colour(t_gamedata *gamedata, int x, int y)
{
	if (x < 0 || x >= MAP_SIZE_MAX || y < 0 || y >= MAP_SIZE_MAX
		|| gamedata->map[y][x].visible || gamedata->map[y][x].e_type == UNBOUND)
		return (BLACK);
	else
		return (gamedata->texture_pack.floor);
}

static void	draw_map_cells_row(t_gamedata *gamedata, t_player *player,
int rel_x, int rel_y)
{
	int			map_x;
	int			map_y;
	t_minimap	*minimap;
	t_rectangle	rect;

	map_x = (int)player->pos.x - rel_x;
	map_y = (int)player->pos.y - rel_y;
	minimap = gamedata->minimap;
	rect.top_x = minimap->wall_offset_x - rel_x * minimap->wall_size;
	rect.bot_x = rect.top_x + minimap->wall_size;
	rect.top_y = minimap->wall_offset_y - rel_y * minimap->wall_size;
	rect.bot_y = rect.top_y + minimap->wall_size;
	while (map_x <= player->pos.x + rel_x)
	{
		rect.colour = get_cell_colour(gamedata, map_x, map_y);
		draw_rectangle_masked(&gamedata->img_buff, &rect,
			&gamedata->minimap->outline);
		rect.top_x = rect.bot_x;
		rect.bot_x += gamedata->minimap->wall_size;
		map_x++;
	}
}

static void	draw_scanlines(t_gamedata *gamedata, t_player *player,
int rel_x, int rel_y)
{
	draw_map_cells_row(gamedata, player, rel_x, rel_y);
	draw_map_cells_row(gamedata, player, rel_x, -rel_y);
	if (rel_x != rel_y)
	{
		draw_map_cells_row(gamedata, player, rel_y, rel_x);
		draw_map_cells_row(gamedata, player, rel_y, -rel_x);
	}
}

static void	render_map_cells(t_gamedata *gamedata, t_player *player)
{
	int	rel_x;
	int	rel_y;
	int	p;

	rel_x = MINIMAP_MAP_RADIUS;
	rel_y = 0;
	p = 1 - MINIMAP_MAP_RADIUS;
	draw_scanlines(gamedata, player, rel_x, rel_y);
	while (rel_x > rel_y)
	{
		rel_y++;
		if (p <= 0)
			p += (2 * rel_y) + 1;
		else
		{
			rel_x--;
			p += (2 * rel_y) - (2 * rel_x) + 1;
		}
		if (rel_x < rel_y)
			break ;
		draw_scanlines(gamedata, &gamedata->player, rel_x, rel_y);
	}
}

void	render_minimap(t_gamedata *gamedata, t_player *player,
t_minimap *minimap)
{
	t_triangle	triangle;

	minimap->wall_offset_x = minimap->screen_x
		- (player->pos.x - (int)player->pos.x) * minimap->wall_size;
	minimap->wall_offset_y = minimap->screen_y
		- (player->pos.y - (int)player->pos.y) * minimap->wall_size;
	render_map_cells(gamedata, player);
	draw_circle(&gamedata->img_buff, &minimap->outline);
	triangle = rotate_minimap_player(minimap, player);
	draw_triangle(&gamedata->img_buff, &triangle);
}
