/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:25:20 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 17:13:21 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release(int key, t_gdata *gd)
{
	if (key == k_ESC)
		mlx_loop_end(gd->mlx);
	else if (key == k_DOWN || key == k_S)
		gd->keys[KEY_DOWN] = false;
	else if (key == k_UP || key == k_W)
		gd->keys[KEY_UP] = false;
	else if (key == k_RIGHT)
		gd->keys[KEY_RIGHT] = false;
	else if (key == k_LEFT)
		gd->keys[KEY_LEFT] = false;
	else if (key == k_D)
		gd->keys[KEY_D] = false;
	else if (key == k_A)
		gd->keys[KEY_A] = false;
	return (1);
}
