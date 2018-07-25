/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:48:12 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/25 23:55:11 by mhoosen          ###   ########.fr       */
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

int main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	set_config(&data);
	data.mlx.ptr = mlx_init();
	if (data.mlx.ptr == NULL)
		die(data, "Failed to intialize mlx");
	data.mlx.win = mlx_new_window(data.mlx.ptr, data.cfg.w, data.cfg.h, "fdf");
	if (data.mlx.win == NULL)
		die(data, "Failed to create window");
	data.img = make_img(data.mlx.ptr, data.cfg.w, data.cfg.h);
	if (data.img.ptr == NULL)
		die(data, "Failed to create image");
	if (data.img.bpp % 8 != 0)
		die(data, "Bad image bit depth");

	data.draw.red = make_colour(data.mlx.ptr, &data.img, 0xFF0000);

	mlx_key_hook(data.mlx.win, key_hook, &data);
	mlx_mouse_hook(data.mlx.win, mouse_hook, &data);
	mlx_expose_hook(data.mlx.win, draw, &data);
	mlx_loop_hook(data.mlx.ptr, draw, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
