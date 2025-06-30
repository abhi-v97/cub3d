/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:14:09 by aistok            #+#    #+#             */
/*   Updated: 2025/06/30 17:13:19 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_gdata *gd)
{
	if (key == k_DOWN || key == k_S)
		gd->keys[KEY_DOWN] = true;
	else if (key == k_UP || key == k_W)
		gd->keys[KEY_UP] = true;
	else if (key == k_RIGHT)
		gd->keys[KEY_RIGHT] = true;
	else if (key == k_LEFT)
		gd->keys[KEY_LEFT] = true;
	else if (key == k_D)
		gd->keys[KEY_D] = true;
	else if (key == k_A)
		gd->keys[KEY_A] = true;
	return (1);
}
