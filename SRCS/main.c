/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchuah <jeremychuahtm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:26:47 by jchuah            #+#    #+#             */
/*   Updated: 2026/01/28 22:54:51 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "inputs.h"
#include "rendering.h"

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
	mlx_mouse_hide(gamedata->display, gamedata->window);
}

static void	init_mlx_imgs(t_gamedata *gamedata,
t_image *img_main, t_image *img_buff)
{
	img_main->mlx_img = mlx_new_image(gamedata->display, WIN_WIDTH, WIN_HEIGHT);
	img_buff->mlx_img = mlx_new_image(gamedata->display, IMG_WIDTH, IMG_HEIGHT);
	if (!img_main->mlx_img || !img_buff->mlx_img)
	{
		ft_putstr_fd("Error\nimage init error", 2);
		close_with_exit_code(gamedata, 127);
	}
	img_main->pixels = mlx_get_data_addr(img_main->mlx_img,
			&img_main->bitsperpixel, &img_main->row_len, &img_main->endian);
	img_buff->pixels = mlx_get_data_addr(img_buff->mlx_img,
			&img_buff->bitsperpixel, &img_buff->row_len, &img_buff->endian);
	img_main->width = WIN_WIDTH;
	img_main->height = WIN_HEIGHT;
	img_buff->width = IMG_WIDTH;
	img_buff->height = IMG_HEIGHT;
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
	mlx_hook(gamedata->window, FocusIn, FocusChangeMask,
		handle_focus_in, gamedata);
	mlx_hook(gamedata->window, FocusOut, FocusChangeMask,
		handle_focus_out, gamedata);
}

int	main(int argc, char *argv[])
{
	t_gamedata		gamedata;
	t_inputs		inputs;
	t_cache	cache;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" <filename.cub>\n", 2);
		return (1);
	}
	gamedata = (t_gamedata){0};
	inputs = (t_inputs){0};
	cache = (t_cache){0};
	gamedata.inputs = &inputs;
	gamedata.cache = &cache;
	init_mlx_displays(&gamedata, argv[1]);
	init_mlx_imgs(&gamedata, &gamedata.img_main, &gamedata.img_buff);
	init_gamedata(&gamedata, argv[1]);
	hook_events(&gamedata);
	mlx_loop(gamedata.display);
	close_and_exit(&gamedata);
}
