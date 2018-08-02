/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 13:47:50 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "lib3d.h"
# include "get_next_line.h"
# include "vec.h"

# include <stdio.h> // aaa
# include <time.h> // aaa

typedef unsigned int	t_uint;

/*
** Keycodes (because the header doesn't exist in OSX)
** mlx uses the codes found in /usr/include/keysymdef.h
*/
# define KEY_ESC		0xff1b
# define KEY_LEFT		0xff51
# define KEY_UP			0xff52
# define KEY_RIGHT		0xff53
# define KEY_DOWN		0xff54
# define KEY_SHIFT		0xffe1
# define KEY_CTRL		0xffe3
# define KEY_M			'm'
# define KEY_W			'w'
# define KEY_S			's'
# define KEY_A			'a'
# define KEY_D			'd'
# define KEY_Q			'q'
# define KEY_E			'e'
# define KEY_R			'r'

# define MOUSE_LEFT		1
# define MOUSE_UP		4
# define MOUSE_DOWN		5

# define KEY_MAX 0xffff
# define MOUSE_MAX 10

/*
** Event codes (because the header doesn't exist in OSX)
** mlx uses the codes found in /usr/include/X11/X.h
*/
# define KEY_PRESS		2
# define KEY_RELEASE	3
# define BUTTON_PRESS	4
# define BUTTON_RELEASE	5
# define MOTION_NOTIFY	6

/*
** A 2D point but with integers
*/
typedef struct	s_ip2d
{
	ssize_t		x;
	ssize_t		y;
}				t_ip2d;

/*
** Stores various mlx handles
*/
typedef struct	s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

/*
** Stores configurable variables (runtime constants)
*/
typedef struct	s_cfg
{
	int			w;
	int			h;
	float		zoom_tick;
	float		z_scale_tick;
	float		zoom_mult;
}				t_cfg;

/*
** Stores an mlx image with the information from mlx_get_data_addr
*/
typedef struct	s_img
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			stride;
	int			endian;
	int			w;
	int			h;
}				t_img;

/*
** A pair of indicies, used to define which points connect to form a line
*/
typedef struct	s_ipair
{
	size_t		a;
	size_t		b;
}				t_ipair;

/*
** Stored variables related to drawing
*/
typedef struct	s_draw
{
	t_p3d		pivot;
	t_p3d		rot;
	t_p3d		m_rot;
	float		dist;
	float		z_scale;
	char		ortho;
	size_t		map_w;
	size_t		map_h;
	t_vec		verts;
	t_vec		lines;
	t_vec		pts;
	t_uint		red;
	t_uint		col_pivot;
}				t_draw;

typedef struct	s_btn
{
	char		down;
	char		changed;
	char		last;
}				t_btn;

typedef struct	s_mouse
{
	int			x;
	int			y;
	t_btn		btn[MOUSE_MAX];
}				t_mouse;

typedef struct	s_input
{
	t_mouse		m;
	char		k[KEY_MAX];
}				t_input;

/*
** Wraps all the data structures so they can be passed to subfunctions
*/
typedef struct	s_data
{
	const t_cfg	cfg;
	t_mlx		mlx;
	t_input		input;
	t_img		img;
	t_draw		draw;
}				t_data;

/*
** Input processing and events
*/
int				on_keyup(int key, t_data *data);
int				on_keydown(int key, t_data *data);
int				on_mouseup(int btn, int x, int y, t_data *data);
int				on_mousedown(int btn, int x, int y, t_data *data);
int				on_mousemove(int x, int y, t_data *data);

int				loop(t_data *data);
int				draw(t_data *data);

/*
** Utilities
*/
int				get_endian(void);
t_uint			swap_endian(t_uint n);
t_img			make_img(void *mlx_ptr, int w, int h);
t_uint			make_colour(void *mlx_ptr, t_img *img, int colour);
void			die(t_data data, char *msg);

t_ip2d			ip2d_add(t_ip2d a, t_ip2d b);
t_ip2d			ip2d_sub(t_ip2d a, t_ip2d b);
int				ip2d_eq(t_ip2d a, t_ip2d b);
int				ip2d_in_rect(t_ip2d p, size_t w, size_t h);
size_t			ip2d_to_i(t_ip2d p, size_t w);

/*
** Image drawing
*/
void			img_put_pixel(t_img *img, int x, int y, t_uint col);
void			img_put_line(t_img *img, t_p2d a, t_p2d b, t_uint col);
void			img_clear(t_img *img);

/*
** Map reading
*/
char			*load_map(t_draw *draw, char *path);

#endif
