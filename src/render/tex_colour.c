/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avalsang <avalsang@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-30 15:27:41 by avalsang          #+#    #+#             */
/*   Updated: 2025-06-30 15:27:41 by avalsang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

// // side: 0 if NS, 1 if WE
// int	get_colour(t_gdata *data, int side)
// {
// 	(void) data;
// 	(void) side;
	
// 	double wall_x;
// 	if (side == 0)
// 		wall_x = data->player.pos.y + perp_dist * ray_dir_y;
// 	else
// 		wall_x = data->player.pos.x + perp_dist * ray_dir_x;
// 	wall_x -= floor(wall_x);

// 	int tex_x = (int)(wall_x * (double)data->tex_size);
// 	if (side == 0 && ray_dir_x > 0)
// 		tex_x = data->tex_size - tex_x - 1;
// 	if (side == 1 && ray_dir_y < 0)
// 		tex_x = data->tex_size - tex_x - 1;
// }
