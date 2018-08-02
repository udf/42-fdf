/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:48:12 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 13:42:14 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO
// COLOURS!!!
// use depth information for culling?
// shift scroll broke?
// check if need double buffer on osx

static void	set_config(t_data *data)
{
	t_cfg *cfg;

	cfg = (t_cfg *)(&data->cfg);
	cfg->w = 900;
	cfg->h = 900;
	cfg->zoom_tick = 1.0f;
	cfg->z_scale_tick = 0.1f;
	cfg->zoom_mult = 5.0f;
}

static void	set_draw(t_data *data)
{
	t_draw *draw;

	draw = &data->draw;
	vec_reserve(&draw->pts, draw->verts.length);
	draw->red = make_colour(data->mlx.ptr, &data->img, 0xFF0000);
	draw->col_pivot = make_colour(data->mlx.ptr, &data->img, 0xCC924A);
	draw->dist = (float)(draw->map_w + draw->map_h / 2);
	draw->pivot = (t_p3d){(float)draw->map_w / 2, (float)draw->map_h / 2, 0};
	draw->rot.x = -45.0f;
	draw->z_scale = 1.0f;
}

static void	register_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, KEY_PRESS, 1L << 0, on_keydown, data);
	mlx_hook(data->mlx.win, KEY_RELEASE, 1L << 1, on_keyup, data);
	mlx_hook(data->mlx.win, BUTTON_PRESS, 1L << 2, on_mousedown, data);
	mlx_hook(data->mlx.win, BUTTON_RELEASE, 1L << 3, on_mouseup, data);
	mlx_hook(data->mlx.win, MOTION_NOTIFY, 1L << 6, on_mousemove, data);
	mlx_expose_hook(data->mlx.win, draw, data);
	mlx_loop_hook(data->mlx.ptr, loop, data);
}

static void	init_vectors(t_draw *draw)
{
	draw->lines.type_size = sizeof(t_ipair);
	draw->verts.type_size = sizeof(t_p3d);
	draw->pts.type_size = sizeof(t_p3d);
}

int			main(int ac, char **av)
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
