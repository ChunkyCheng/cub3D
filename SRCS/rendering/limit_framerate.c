/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_framerate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lming-ha <lming-ha@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 11:09:35 by jchuah            #+#    #+#             */
/*   Updated: 2026/02/03 18:09:22 by jchuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "rendering.h"
#include <sys/time.h>

static t_llong	get_usec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

static void	busy_sleep(t_llong elapsed)
{
	t_llong	frame_time;
	t_llong	start;
	t_llong	now;

	frame_time = 1000000 / FRAMERATE;
	if (elapsed >= frame_time)
		return ;
	start = get_usec();
	while (1)
	{
		now = get_usec();
		if ((now - start + elapsed) >= frame_time)
			break ;
	}
}

static void	print_fps(void)
{
	static int		frames = 0;
	static long		last_time = 0;
	long			now;
	static double	fps;

	now = get_usec();
	if (last_time == 0)
	{
		last_time = now;
		frames = 0;
		return ;
	}
	frames++;
	if ((now - last_time) >= 1000000)
	{
		fps = frames * 1000000.0 / (now - last_time);
		printf("FPS: %.2f\n", fps);
		frames = 0;
		last_time = now;
	}
}

void	limit_framerate(void)
{
	static t_llong	prev = 0;
	t_llong			elapsed;

	if (prev == 0)
	{
		prev = get_usec();
		return ;
	}
	elapsed = get_usec() - prev;
	busy_sleep(elapsed);
	prev = get_usec();
	if (DEBUG)
		print_fps();
}
