/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:26:47 by jchuah            #+#    #+#             */
/*   Updated: 2025/12/16 09:57:33 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"

static char	*create_title(char *title)
{
	char	*temp;

	if (ft_strchr(title, '/'))
		title = ft_strrchr(title, '/') + 1;
	temp = ft_strjoin("cub3D - ", title);
	return (temp);
}

static void	init_mlx_displays(t_gamedata *gamedata, char *title)
{
	gamedata->display = mlx_init();
	if (!gamedata->display)
	{
		ft_putstr_fd("Error\nmlx init error", 2);
	}
	title = create_title(title);
	gamedata->window
		= mlx_new_window(gamedata->display, WIN_WIDTH, WIN_HEIGHT, title);
	free(title);
	if (!gamedata->window)
	{
		ft_putstr_fd("Error\nwindow init error", 2);
		close_with_exit_code(gamedata, 127);
	}
}

static void	init_mlx_img_main(t_gamedata *gamedata)
{
	gamedata->img_main.mlx_img
		= mlx_new_image(gamedata->display, WIN_WIDTH, WIN_HEIGHT);
	if (!gamedata->img_main.mlx_img)
	{
		ft_putstr_fd("Error\nimage init error", 2);
		close_with_exit_code(gamedata, 127);
	}
	gamedata->img_main.pixels = mlx_get_data_addr(gamedata->img_main.mlx_img,
			&gamedata->img_main.bitsperpixel, &gamedata->img_main.row_len,
			&gamedata->img_main.endian);
	gamedata->img_main.width = WIN_WIDTH;
	gamedata->img_main.height = WIN_HEIGHT;
}

static void	hook_events(t_gamedata *gamedata)
{
	mlx_loop_hook(gamedata->display, game_loop, gamedata);
	mlx_hook(gamedata->window, DestroyNotify, 0, close_and_exit, gamedata);
	mlx_hook(gamedata->window, KeyPress, KeyPressMask,
		handle_key_press, gamedata);
	mlx_hook(gamedata->window, KeyRelease, KeyReleaseMask,
		handle_key_release, gamedata);
	mlx_hook(gamedata->window, ButtonPress, ButtonPressMask,
		handle_mouse_press, gamedata);
	mlx_hook(gamedata->window, ButtonRelease, ButtonReleaseMask,
		handle_mouse_release, gamedata);
	mlx_hook(gamedata->window, MotionNotify, PointerMotionMask,
		handle_mouse_move, gamedata);
}

int	main(int argc, char *argv[])
{
	t_gamedata	gamedata;
	t_inputs	inputs;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" <filename.cub>\n", 2);
		return (1);
	}
	gamedata = (t_gamedata){0};
	inputs = (t_inputs){0};
	gamedata.inputs = &inputs;
	init_mlx_displays(&gamedata, argv[1]);
	init_mlx_img_main(&gamedata);
	init_gamedata(&gamedata, argv[1]);
	hook_events(&gamedata);
	mlx_loop(gamedata.display);
	close_and_exit(&gamedata);
}
