/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:31:35 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/30 16:45:38 by lming-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

# define DFL_FLOOR		0x393A40
# define DFL_CEILING	0x1A1C20

# define DFL_NORTH		"textures/wall-default-north.xpm"
# define DFL_SOUTH		"textures/wall-default-south.xpm"
# define DFL_WEST		"textures/wall-default-west.xpm"
# define DFL_EAST		"textures/wall-default-east.xpm"

typedef struct s_render_vals	t_render_vals;

typedef struct s_parsing
{
	enum
	{
		ELEMENTS,
		MAP
	}		e_state;
	int		fd;
	char	*identifier;
	int		wall_idx;
	int		wall[8];
	char	*info;
	t_map	map;
}	t_parsing;

int		open_valid_ext(char *path, char *extension, int *out_fd);
int		get_wall(char c);
void	parsing_cleanup(t_parsing *p_data);
void	clean_error(t_parsing *p_data, t_gamedata *gamedata, char *message);

void	parse_element(char *line, t_gamedata *gamedata, t_parsing *p_data);
void	parse_colour(t_gamedata *gamedata, t_parsing *p_data);
void	parse_texture(t_gamedata *gamedata, t_parsing *p_data);
void	element_checklist(t_gamedata *gamedata, t_parsing *p_data);
int		add_map_line(char *line, t_parsing *p_data, t_gamedata *gamedata);
void	pad_map(t_map *map, t_parsing *p_data, t_gamedata *gamedata);
void	trim_map(t_map *map, t_parsing *p_data, t_gamedata *gamedata);
void	parse_player(t_gamedata *gamedata, t_parsing *p_data);
void	validate_map(t_gamedata *gamedata, t_parsing *p_data);
void	flood_fill(t_map *map, int **mask, int x, int y);
int		check_edge_flood(t_map *map, int **mask, int x, int y);

void	init_render_vals(t_render_vals *render_vals);

#endif
