/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:50:20 by aistok            #+#    #+#             */
/*   Updated: 2025/07/09 22:57:20 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_usage(int argc, char **argv)
{
	(void) argc;
	ft_errmsg("Usage: ");
	ft_errmsg(argv[0]);
	ft_errmsg(" map_file.cub\n");
}
