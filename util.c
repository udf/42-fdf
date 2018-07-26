/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:25:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/26 13:04:26 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_endian(void)
{
	unsigned int endian_test;
	static int endian = -1;

	if (endian < 0)
	{
		endian_test = 0xAABBCCDD;
		endian = *((unsigned char *)&endian_test) == 0xAA;
	}
	return (endian);
}

unsigned int	swap_endian(unsigned int n)
{
	return (
		((n << 24) & 0xFF000000) |
		((n << 8) &  0xFF0000) |
		((n >> 8) &  0xFF00) |
		((n >> 24) & 0xFF)
	);
}

unsigned int	make_colour(void *mlx_ptr, t_img *img, int colour)
{
	unsigned int col;

	col = mlx_get_color_value(mlx_ptr, colour);
	if (img->endian != get_endian())
		col = swap_endian(col);
	return (col);
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
	return (img);
}

void	die(t_data data, char *msg)
{
	if (msg && *msg)
		ft_putendl_fd(msg, 2);
	if (data.img.ptr)
	{
		printf("Destroying image...\n");
		mlx_destroy_image(data.mlx.ptr, data.img.ptr);
	}
	if (data.mlx.win)
	{
		printf("Destroying window...\n");
		mlx_destroy_window(data.mlx.ptr, data.mlx.win);
	}
	printf("exiting...\n");
	exit(0);
}


