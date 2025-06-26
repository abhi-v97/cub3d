/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:34:50 by aistok            #+#    #+#             */
/*   Updated: 2025/06/26 16:32:46 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_gdata *gdata)
{
	const int	step = 10;

	if (gdata->keys[KEY_UP])
		gdata->player.pos.y -= step;
	else if (gdata->keys[KEY_DOWN])
		gdata->player.pos.y += step;
	else if (gdata->keys[KEY_RIGHT])
		gdata->player.pos.x += step;
	else if (gdata->keys[KEY_LEFT])
		gdata->player.pos.x -= step;
	if (gdata->player.pos.x < 0)
		gdata->player.pos.x = W_WIDTH;
	else if (gdata->player.pos.x > W_WIDTH)
		gdata->player.pos.x = 0;
	if (gdata->player.pos.y < 0)
		gdata->player.pos.y = W_HEIGHT;
	else if (gdata->player.pos.y > W_HEIGHT)
		gdata->player.pos.y = 0;
}

void	render_player(t_gdata *gdata)
{
	put_pixel(&gdata->canvas,
		(int)gdata->player.pos.x,
		(int)gdata->player.pos.y,
		0x00FFFFFF);
}

int	render_screen(void *param)
{
	t_gdata	*gd = param;
	int		limit;
	int		*data;
	int		i;

	data = (int *)gd->canvas.addr;
	limit = gd->canvas.w * gd->canvas.h;
	i = 0;
	while (i < limit)
		data[i++] = 0x000000ff;
	move_player(gd);
	put_pixel(&gd->canvas,
		(int)gd->player.pos.x,
		(int)gd->player.pos.y,
		0x00FFFFFF);
	mlx_put_image_to_window(gd->display, gd->win, gd->canvas.img, 0, 0);
	usleep(100000);
	return (1);
}
