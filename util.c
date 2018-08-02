/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:25:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 21:09:03 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	flerpf(float frac, float start, float end)
{
	return (start + (end - start) * frac);
}

t_p2d	t_p2d_lerp(float frac, t_p2d start, t_p2d end)
{
	return (t_p2d){start.x + (end.x - start.x) * frac,
		start.y + (end.y - start.y) * frac};
}

t_p2d	p2d_roundf(t_p2d p)
{
	return (t_p2d){roundf(p.x), roundf(p.y)};
}

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
	img.z_buf = malloc(sizeof(float) * (size_t)w * (size_t)h);
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
