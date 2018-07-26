/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:48:12 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/26 23:46:23 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO
// figure out how mouse and keyboard work on osx
// fix mlx-x11 mouse and keyboard to work like osx

void set_config(t_data *data)
{
	t_cfg *cfg;

	cfg = (t_cfg *)(&data->cfg);
	cfg->w = 900;
	cfg->h = 900;
}

void set_draw(t_data *data)
{
	t_draw *draw;

	draw = &data->draw;
	draw->red = make_colour(data->mlx.ptr, &data->img, 0xFF0000);
	draw->cam.pos.z = 5;
}

char	*load_map(t_draw *draw, char *path)
{
	int fd;
	t_p3d p;
	t_ipair l;

	if ((fd = open(path, O_RDONLY)) < 0)
		return "Failed to open map file";
	// TODO: actually read map file;
	close(fd);
	draw->verts.type_size = sizeof(t_p3d);
	draw->lines.type_size = sizeof(t_ipair);
	draw->pts.type_size = sizeof(t_p2d);
	draw->visible_pts.type_size = sizeof(int);

	p = (t_p3d){0, 0, 0};
	vec_append(&draw->verts, &p);
	p = (t_p3d){1, 0, 0};
	vec_append(&draw->verts, &p);
	p = (t_p3d){1, 1, 0};
	vec_append(&draw->verts, &p);
	p = (t_p3d){0, 1, 0};
	vec_append(&draw->verts, &p);

	p = (t_p3d){0, 0, 1};
	vec_append(&draw->verts, &p);
	p = (t_p3d){1, 0, 1};
	vec_append(&draw->verts, &p);
	p = (t_p3d){1, 1, 1};
	vec_append(&draw->verts, &p);
	p = (t_p3d){0, 1, 1};
	vec_append(&draw->verts, &p);

	l = (t_ipair){0, 1};
	vec_append(&draw->lines, &l);
	l = (t_ipair){1, 2};
	vec_append(&draw->lines, &l);
	l = (t_ipair){2, 3};
	vec_append(&draw->lines, &l);
	l = (t_ipair){3, 0};
	vec_append(&draw->lines, &l);

	l = (t_ipair){4, 5};
	vec_append(&draw->lines, &l);
	l = (t_ipair){5, 6};
	vec_append(&draw->lines, &l);
	l = (t_ipair){6, 7};
	vec_append(&draw->lines, &l);
	l = (t_ipair){7, 4};
	vec_append(&draw->lines, &l);

	l = (t_ipair){0, 4};
	vec_append(&draw->lines, &l);
	l = (t_ipair){1, 5};
	vec_append(&draw->lines, &l);
	l = (t_ipair){2, 6};
	vec_append(&draw->lines, &l);
	l = (t_ipair){3, 7};
	vec_append(&draw->lines, &l);

	vec_reserve(&draw->pts, draw->verts.length);
	vec_reserve(&draw->visible_pts, draw->verts.length);

	return (NULL);
}

void	register_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, KeyPress, KeyPressMask, on_keydown, data);
	mlx_hook(data->mlx.win, KeyRelease, KeyReleaseMask, on_keyup, data);
	mlx_hook(data->mlx.win, ButtonPress, ButtonPressMask, on_mousedown, data);
	mlx_hook(data->mlx.win, ButtonRelease, ButtonReleaseMask, on_mouseup, data);
	mlx_hook(data->mlx.win, MotionNotify, PointerMotionMask, on_mousemove, data);
	mlx_expose_hook(data->mlx.win, draw, data);
	mlx_loop_hook(data->mlx.ptr, draw, data);
}

int main(int ac, char **av)
{
	t_data	data;
	char	*err;

	ft_bzero(&data, sizeof(t_data));
	err = "No map file provided";
	if (ac <= 1 || (err = load_map(&data.draw, av[1])))
		die(data, err);
	set_config(&data);
	if ((data.mlx.ptr = mlx_init()) == NULL)
		die(data, "Failed to intialize mlx");
	data.mlx.win = mlx_new_window(data.mlx.ptr, data.cfg.w, data.cfg.h, "fdf");
	if (data.mlx.win == NULL)
		die(data, "Failed to create window");
	data.img = make_img(data.mlx.ptr, data.cfg.w, data.cfg.h);
	if (data.img.ptr == NULL || data.img.bpp % 8 != 0)
		die(data, "Failed to create image");
	set_draw(&data);
	register_hooks(&data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
