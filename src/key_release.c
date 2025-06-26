/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:25:20 by aistok            #+#    #+#             */
/*   Updated: 2025/06/26 14:49:19 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_release(int key, t_gdata *gdata)
{
	if (key == k_DOWN)
		gdata->keys[KEY_DOWN] = false;
	else if (key == k_UP)
		gdata->keys[KEY_UP] = false;
	else if (key == k_RIGHT)
		gdata->keys[KEY_RIGHT] = false;
	else if (key == k_LEFT)
		gdata->keys[KEY_LEFT] = false;
	if (key == k_ESC) // TO-DO: this gives a segfault !!!
		mlx_loop_end(gdata->display);
	return (1);
}
