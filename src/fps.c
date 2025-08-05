/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 14:57:33 by abhi              #+#    #+#             */
/*   Updated: 2025/08/05 18:57:41 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

int	get_time_stamp(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}

static int	num_len(int n);

//	update gd->frame_time, used for movement and rotation
//	timing for input and FPS counter
//	frameTime is the time this frame has taken to generate (in seconds)
void	update_frame_time(t_gdata *gd)
{
	static char		temp[10];
	static int		fps_time;
	int				fps;
	int				i;

	gd->old_time = gd->time;
	gd->time = get_time_stamp();
	gd->frame_time = (gd->time - gd->old_time) / 10000000.0;
	if (fps_time == 0)
		fps_time = gd->old_time;
	if ((gd->time - fps_time) > 1000000)
	{
		fps = (1 / gd->frame_time);
		i = num_len(fps);
		temp[i--] = '\0';
		while (fps)
		{
			temp[i--] = (fps % 10) + '0';
			fps /= 10;
		}
		fps_time = gd->time;
	}
	mlx_string_put(gd->mlx, gd->win, 10, 10, 0xFF00, temp);
}

static int	num_len(int n)
{
	int		i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
