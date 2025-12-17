/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 02:35:05 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/17 12:51:15 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

# include "cub3d.h"

# define W_HOLD			0b0001
# define A_HOLD			0b0010
# define S_HOLD			0b0100
# define D_HOLD			0b1000

# define LEFT_HOLD		0b01
# define RIGHT_HOLD		0b10

# define LCLICK_HOLD	0b01

# define MOVE_SPEED			0.04
# define ROT_SPEED_KEY		0.8
# define ROT_SPEED_MOUSE	0.07

typedef struct s_inputs
{
	int	move_flags;
	int	rot_flags;
	int	click_flags;
	int	mouse_x;
	int	mouse_y;
	int	x_move;
	int	y_move;
	int	focused;
}	t_inputs;

void	hide_cursor(void *display, void *window, int activate);
void	lock_mouse(void	*display, void *window);

int		handle_key_press(int key, t_gamedata *gamedata);
int		handle_key_release(int key, t_gamedata *gamedata);
int		handle_mouse_press(int button, int x, int y, t_gamedata *gamedata);
int		handle_mouse_release(int button, int x, int y, t_gamedata *gamedata);
int		handle_mouse_move(int x, int y, t_gamedata *gamedata);
int		handle_focus_in(t_gamedata *gamedata);
int		handle_focus_out(t_gamedata *gamedata);

void	check_inputs(t_gamedata *gamedata, t_inputs *inputs,
			t_player *player);
void	handle_movement(t_inputs *inputs, t_player *player);
void	handle_rotation(t_inputs *inputs, t_player *player);

#endif
