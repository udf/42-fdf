/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/31 11:46:45 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h> // aaa
# include "libft.h"
# include "lib3d.h"
# include "get_next_line.h"
# include "vec.h"

typedef unsigned int t_uint;

/*
** Keycodes (because the header doesn't exist in OSX)
** mlx uses the codes found in /usr/include/keysymdef.h
*/
# define KEY_Escape		0xff1b
# define KEY_Left		0xff51
# define KEY_Up			0xff52
# define KEY_Right		0xff53
# define KEY_Down		0xff54
# define KEY_Shift		0xffe1
# define KEY_Ctrl		0xffe3
# define KEY_m			'm'
# define KEY_w			'w'
# define KEY_s			's'
# define KEY_a			'a'
# define KEY_d			'd'
# define KEY_q			'q'
# define KEY_e			'e'
# define KEY_r			'r'

# define MOUSE_Left		1
# define MOUSE_Mid		2
# define MOUSE_Right	3
# define MOUSE_Up		4
# define MOUSE_Down		5

# define KEY_MAX 0xffff
# define MOUSE_MAX 10

/*
** Event codes and masks (because the header doesn't exist in OSX)
** mlx uses the codes found in /usr/include/X11/X.h
*/
#define KeyPress		2
#define KeyRelease		3
#define ButtonPress		4
#define ButtonRelease	5
#define MotionNotify	6

#define KeyPressMask			(1L<<0)
#define KeyReleaseMask			(1L<<1)
#define ButtonPressMask			(1L<<2)
#define ButtonReleaseMask		(1L<<3)
#define PointerMotionMask		(1L<<6)

/*
** A 2D point but with integers
*/
typedef struct
{
	ssize_t		x;
	ssize_t		y;
}				t_ip2d;

/*
** Stores various mlx handles
*/
typedef struct
{
	void		*ptr;
	void		*win;
}				t_mlx;

/*
** Stores configurable variables (runtime constants)
*/
typedef struct
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
typedef struct
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
typedef struct
{
	size_t		a;
	size_t		b;
}				t_ipair;

/*
** Stored variables related to drawing
*/
typedef struct
{
	t_p3d		pivot;
	t_p3d		rot;
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

typedef struct
{
	char		down;
	char		changed;
	char		last;
}				t_btn;

typedef struct
{
	int			x;
	int			y;
	t_btn		btn[MOUSE_MAX];
}				t_mouse;

typedef struct
{
	t_mouse		m;
	int			k[KEY_MAX];
}				t_input;

/*
** Wraps all the data structures so they can be passed to subfunctions
*/
typedef struct
{
	const t_cfg	cfg;
	t_mlx		mlx;
	t_input		input;
	t_img		img;
	t_draw		draw;
}				t_data;

/*
** Events
*/
int				on_keyup(int key, void *param);
int				on_keydown(int key, void *param);
int				on_mouseup(int btn, int x, int y, void *param);
int				on_mousedown(int btn, int x, int y, void *param);
int				on_mousemove(int x, int y, void *param);
int				loop(void *param);
int				draw(t_data *data);

/*
** Utilities
*/
int				get_endian(void);
unsigned int	swap_endian(unsigned int n);
t_img			make_img(void *mlx_ptr, int w, int h);
unsigned int	make_colour(void *mlx_ptr, t_img *img, int colour);
void			die(t_data data, char *msg);

t_ip2d			ip2d_add(t_ip2d a, t_ip2d b);
t_ip2d			ip2d_sub(t_ip2d a, t_ip2d b);
int				ip2d_eq(t_ip2d a, t_ip2d b);
int				ip2d_in_rect(t_ip2d p, size_t w, size_t h);
size_t			ip2d_to_i(t_ip2d p, size_t w);

/*
** Image drawing
*/
void			img_put_pixel(t_img *img, int x, int y, unsigned int col);
void			img_put_line(t_img *img, t_p2d a, t_p2d b, unsigned int col);
void			img_clear(t_img *img);


#endif
