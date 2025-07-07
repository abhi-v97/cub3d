/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 17:23:16 by aistok            #+#    #+#             */
/*   Updated: 2025/07/07 22:03:04 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	rendering_function(void *param)
{
	t_gdata *gd;
	t_ray	ray;
	t_ipos	map_pos;
	int		x;

	gd = (t_gdata *)param;
	render_background(gd);
	x = -1;
	while (++x < W_WIDTH)
	{
		map_pos = pos_dtoi(gd->player.pos);
		ray = ray_create(gd, x, &map_pos);
		if (ray_hits_map(gd, &ray, &map_pos))
		{
			ray.line_height = line_height(gd, &ray);
			calc_draw_distance(&ray);
			draw_wall(gd, ray, x); //draw_wall_plain(gd, &ray, x, 0x0000FF00);
		}
	}
	mlx_put_image_to_window(gd->mlx, gd->win, gd->canvas.img, 0, 0);	
	update_frame_time(gd);
	handle_key_presses(gd);
	return (1);
}
