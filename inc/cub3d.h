/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:44:25 by avalsang          #+#    #+#             */
/*   Updated: 2025/06/23 16:32:35 by aistok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "../minilibx-linux/mlx.h"

# define EMLXERR 1
# define EMLXWINERR 2

# define k_ESC 65307
# define k_LEFT 65361
# define k_UP 65362
# define k_RIGHT 65363
# define k_DOWN 65364
# define k_LT 44
# define k_GT 46
# define k_SQB1 91
# define k_SQB2 93
# define k_A 97
# define k_C 99
# define k_L 108
# define k_D 100
# define k_R 114
# define k_S 115
# define k_W 119
# define k_X 120

# define DN 1
# define DS 2
# define DE 3
# define DW 4

/*
 *	bpp - bit per pixel
 *	ll	- line length
 */
typedef struct s_canvas
{
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		w;
	int		h;
}	t_canvas;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

/*
 *	(x, y)	position of the player on the map and in the "game"
 *	dir		direction the player is facing (DN | DS | DE | DW)
 */
typedef struct s_player
{
	t_pos	pos;
	int		dir;
}	t_player;

typedef struct s_gdata
{
	void		*display;
	char		**map;
	int			file_fd;
	int			map_height;
	void		*win;
	t_canvas	cnvs;
	int			ww;
	int			wh;
	int			exit_code;
	t_player	player;
}	t_gdata;

// libft funcs
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);
char	*ft_strdup(const char *src);
char	*get_next_line(int fd);

// parsing/check_arg.c
int		check_arg(char *file);

// parsing/parse_file.c
int		parse_file(t_gdata *gdata, char *file);

// parsing/check_map.c
int		check_map(t_gdata *data);

// error.c
void	ft_error(char *msg);

// utils.c
int		is_blank(char c);

// init.c
void	init_data(t_gdata *gdata);
bool	init_graphics(t_gdata *gdata);

// player_get_pos.c
t_pos	player_get_pos_from_map(t_gdata *gdata);

#endif
