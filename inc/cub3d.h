/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aistok <aistok@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:44:25 by avalsang          #+#    #+#             */
/*   Updated: 2025/06/26 14:45:22 by aistok           ###   ########.fr       */
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
# include "mlx.h"

# define EMLXERR 500
# define EMLXWINERR 501

# ifndef W_WIDTH
#  define W_WIDTH 800
# endif

# ifndef W_HEIGHT
#  define W_HEIGHT 600
# endif

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

# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4

# define KEY_COUNT 5
# define KEY_UP 0
# define KEY_DOWN 1
# define KEY_LEFT 2
# define KEY_RIGHT 3
# define KEY_ESC 4

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
	double	angle;
}	t_pos;

/*
 *	(x, y)	position of the player on the map and in the "game"
 *	angle	direction the player is looking at:
 *			angle 0 faces NORTH (precisely)
 *			angle 90 faces EAST (precisely)
 *			angle 180 faces SOUTH (precisely)
 *			angle 270 faces WEST (precisely)
 */
typedef struct s_player
{
	t_pos	pos;
}	t_player;

/*
 *	gdata - Game data
 *
 *	player_direction: used to set starting direction of player
 *	should probably make a separate struct for player and link it here
 */
typedef struct s_gdata
{
	void		*display;
	char		**map;
	int			file_fd;
	int			player_direction;
	int			map_height;
	int			map_width;
	int			wall_width;
	int			wall_height;
	void		*win;
	t_canvas	canvas;
	int			ww;
	int			wh;
	int			exit_code;
	int			keys[KEY_COUNT];
	t_player	player;
}	t_gdata;

// libft funcs
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*get_next_line(int fd);
char	*ft_strdup(const char *src);
char	*ft_strndup(const char *s, int n);
char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);

// parsing/check_arg.c
int		check_arg(char *file);

// parsing/parse_file.c
int		parse_file(t_gdata *gdata, char *file);

// parsing/check_map.c
int		check_map(t_gdata *data);

// parsing/check_bounds.c
int		check_map_bounds(t_gdata *data, char **map, int map_height);

// error.c
void	ft_error(char *msg);

// utils.c
int		is_blank(char c);

// init.c
void	init_gdata(t_gdata *gdata);
bool	init_graphics(t_gdata *gdata);

// cleanup.c
void    cleanup(t_gdata *gdata);

// put_pixel.c
void	put_pixel(t_canvas *cdata, int x, int y, int color);

// player_get_pos.c
t_pos	player_get_pos_from_map(t_gdata *gdata);
double	pos_nsew_to_angle(char c);
t_pos	pos_init_to_invalid_pos(void);
t_pos	pos_set_to(double x, double y, double angle);

int	key_handler(int key, t_gdata *gdata);
int	key_press(int key, t_gdata *gdata);
int	key_release(int key, t_gdata *gdata);

// rendering/render_screen.c
int	render_screen(void *param);

#endif
