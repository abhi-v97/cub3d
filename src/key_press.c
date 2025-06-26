/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:14:09 by aistok            #+#    #+#             */
/*   Updated: 2025/06/26 14:48:47 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_gdata *gdata)
{
	if (key == k_DOWN)
		gdata->keys[KEY_DOWN] = true;
	else if (key == k_UP)
		gdata->keys[KEY_UP] = true;
	else if (key == k_RIGHT)
		gdata->keys[KEY_RIGHT] = true;
	else if (key == k_LEFT)
		gdata->keys[KEY_LEFT] = true;
	return (1);
}
