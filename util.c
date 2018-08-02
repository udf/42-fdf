/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:25:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 20:39:34 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img	make_img(void *mlx_ptr, int w, int h)
{
	t_img img;

	img.ptr = mlx_new_image(mlx_ptr, w, h);
	if (!img.ptr)
		return (img);
	img.data = mlx_get_data_addr(img.ptr,
		&img.bpp, &img.stride, &img.endian);
	img.w = w;
	img.h = h;
	return (img);
}

void	die(t_data data, char *msg)
{
	if (msg && *msg)
		ft_putendl_fd(msg, 2);
	vec_free(&data.draw.verts);
	vec_free(&data.draw.pts);
	vec_free(&data.draw.lines);
	vec_free(&data.draw.colmap);
	if (data.img.ptr)
		mlx_destroy_image(data.mlx.ptr, data.img.ptr);
	free(data.img.z_buf);
	if (data.mlx.win)
		mlx_destroy_window(data.mlx.ptr, data.mlx.win);
	exit(0);
}
