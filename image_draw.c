/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 23:42:28 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/01 21:54:05 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_put_pixel(t_img *img, int x, int y, unsigned int col)
{
	const int bytes_pp = img->stride / img->w;
	char *data;

	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	data = img->data + x * bytes_pp + y * img->stride;
	*((unsigned int *)data) = col;
}

static void	point_clip(t_p2d *p, float w, float h, float m, float im)
{
	t_p2d	clamped;

	clamped.x = CLAMP(p->x, 0, w - 1.0f);
	if (isfinite(m))
		p->y = m * (clamped.x - p->x) + p->y;
	p->x = clamped.x;
	clamped.y = CLAMP(p->y, 0, h - 1.0f);
	if (isfinite(im))
		p->x = im * (clamped.y - p->y) + p->x;
	p->y = clamped.y;
}

static int	line_clip(t_p2d *a, t_p2d *b, float w, float h)
{
	const float m = (b->y - a->y) / (b->x - a->x);
	const float im = (b->x - a->x) / (b->y - a->y);

	point_clip(a, w, h, m, im);
	point_clip(b, w, h, m, im);
	return ((a->x < 0 || a->x >= w || a->y < 0 || a->y >= h)
				&& (b->x < 0 || b->x >= w || b->y < 0 || b->y >= h));
}

void	img_put_line(t_img *img, t_p2d a, t_p2d b, unsigned int col)
{
	long i;
	long steps;
	t_p2d p;

	if (line_clip(&a, &b, (float)img->w, (float)img->h))
		return ;
	a.x = roundf(a.x);
	a.y = roundf(a.y);
	b.x = roundf(b.x);
	b.y = roundf(b.y);
	steps = (long)MAX(ABS(b.x - a.x), ABS(b.y - a.y));
	i = 0;
	while (i < steps)
	{
		p = (t_p2d){ft_lmapf(i, 0, steps, a.x, b.x),
					ft_lmapf(i, 0, steps, a.y, b.y)};
		img_put_pixel(img, (int)roundf(p.x), (int)roundf(p.y), col);
		i++;
	}
}

void	img_clear(t_img *img)
{
	const size_t	len = (size_t)(img->stride * img->h) / sizeof(t_uint);
	t_uint			*data;
	size_t			i;

	data = (t_uint *)img->data;
	/* debug: if red flickering is seen then need double buffer
	i = 0;
	while (i < len)
	{
		data[i] = 0xFF0000;
		i++;
	}*/
	i = 0;
	while (i < len)
	{
		data[i] = 0;
		i++;
	}
}
