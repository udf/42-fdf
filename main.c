/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:48:12 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/29 05:28:01 by mhoosen          ###   ########.fr       */
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
	cfg->zoom_tick = 1.0f;
}

void set_draw(t_data *data)
{
	t_draw *draw;

	draw = &data->draw;
	vec_reserve(&draw->pts, draw->verts.length);
	vec_reserve(&draw->visible_pts, draw->verts.length);
	draw->red = make_colour(data->mlx.ptr, &data->img, 0xFF0000);

	draw->dist = 20.0f;
	draw->pivot = (t_p3d){(float)draw->map_w / 2, (float)draw->map_h / 2, 0};
	draw->rot.x = -45.0f;
}

char		*read_vert_row(t_draw *draw, size_t y, char **split)
{
	size_t	w;
	t_p3d	p;

	w = 0;
	p.y = (float)y;
	while (*split)
	{
		p.z = (float)ft_atoi(*split);
		p.x = (float)w;
		vec_append(&draw->verts, &p);
		w++;
		split++;
	}
	if (!draw->map_w)
		draw->map_w = w;
	if (w != draw->map_w || w == 0)
		return ("Invalid number of heights in map");
	return (NULL);
}

void	make_lines(t_draw *draw, t_ip2d start, t_ip2d dir)
{
	const size_t w = draw->map_w;
	const size_t h = draw->map_h;
	t_ip2d end;
	t_ipair l;

	while (ip2d_in_rect(ip2d_add(start, dir), w, h))
	{
		end = ip2d_add(start, dir);
		if (!ip2d_in_rect(end, w, h))
			return ;
		l = (t_ipair){ip2d_to_i(start, w), ip2d_to_i(end, w)};
		vec_append(&draw->lines, &l);
		start = end;
	}
}

void	make_grid_lines(t_draw *draw)
{
	t_ip2d	start;

	start.x = 0;
	start.y = 0;
	while (start.y < (ssize_t)draw->map_h)
	{
		make_lines(draw, start, (t_ip2d){1, 0});
		start.y++;
	}
	start.y = 0;
	while (start.x < (ssize_t)draw->map_w)
	{
		make_lines(draw, start, (t_ip2d){0, 1});
		start.x++;
	}
}

char	*load_map(t_draw *draw, char *path)
{
	int fd;
	char *line;
	char **split;

	if ((fd = open(path, O_RDONLY)) < 0)
		return "Failed to open map file";
	draw->map_h = 0;
	while (get_next_line(fd, &line) == GNL_SUCCESS)
	{
		split = ft_strsplit(line, ' ');
		free(line);
		if (!split)
			return "Failed to read map line";
		line = read_vert_row(draw, draw->map_h, split);
		free(split);
		if (line)
			return (line);
		draw->map_h++;
	}
	close(fd);
	if (draw->map_h == 0)
		return "Error: Map is empty";
	make_grid_lines(draw);
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

void init_vectors(t_draw *draw)
{
	draw->lines.type_size = sizeof(t_ipair);
	draw->verts.type_size = sizeof(t_p3d);
	draw->pts.type_size = sizeof(t_p2d);
	draw->visible_pts.type_size = sizeof(int);
}

int main(int ac, char **av)
{
	t_data	data;
	char	*err;

	ft_bzero(&data, sizeof(t_data));
	init_vectors(&data.draw);
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
