/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:49:29 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/26 23:43:45 by mhoosen          ###   ########.fr       */
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
	t_v3d		cam;
	t_vec		verts;
	t_vec		lines;
	t_vec		pts;
	t_vec		visible_pts;
	t_uint		red;
}				t_draw;

typedef struct	s_mouse
{
	int			x;
	int			y;
	int			btn[MOUSE_MAX];
}				t_mouse;

typedef struct	s_input
{
	t_mouse		m;
	int			k[KEY_MAX];
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
** Events
*/
int on_keyup(int key, void *param);
int on_keydown(int key, void *param);
int on_mouseup(int btn, int x, int y, void *param);
int on_mousedown(int btn, int x, int y, void *param);
int on_mousemove(int x, int y, void *param);
int draw(void *param);

/*
** Utilities
*/
int				get_endian(void);
unsigned int	swap_endian(unsigned int n);
t_img			make_img(void *mlx_ptr, int w, int h);
unsigned int	make_colour(void *mlx_ptr, t_img *img, int colour);
void			die(t_data data, char *msg);

/*
** Image drawing
*/
void	img_put_pixel(t_img *img, int x, int y, unsigned int col);
void	img_put_line(t_img *img, t_p2d a, t_p2d b, unsigned int col);
void	img_clear(t_img *img);


#endif
