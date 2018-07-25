/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 22:14:07 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/26 00:09:53 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_putpixel(t_img *img, int x, int y, unsigned int col)
{
	const int bytes_pp = img->bpp / 8;
	char *data;

	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	data = img->data + x * bytes_pp + y * img->stride;
	ft_memcpy((void *)data, (void*)&col, (size_t)bytes_pp);
}

void	img_clear(t_img *img)
{
	ft_bzero((void *)img->data, (size_t)(img->stride * img->h));
}

int	draw(void *param)
{
	t_data *data = (t_data *)param;

	if (data->draw.d.x == 0)
	{
		data->draw.d.x = 0.1f;
		data->draw.d.y = 0.8f;
	}

	data->draw.q.x += data->draw.d.x;
	data->draw.q.y += data->draw.d.y;

	if (data->draw.q.x < 0)
		data->draw.d.x *= -1;
	if (data->draw.q.x >= data->img.w)
		data->draw.d.x *= -1;
	if (data->draw.q.y < 0)
		data->draw.d.y *= -1;
	if (data->draw.q.y >= data->img.h)
		data->draw.d.y *= -1;

	img_clear(&data->img);
	img_putpixel(&data->img, (int)data->draw.q.x, (int)data->draw.q.y, data->draw.red);

	//printf("draw\n");
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->img.ptr, 0, 0);
	return 0;
}
