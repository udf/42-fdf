/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 23:42:28 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/26 23:43:52 by mhoosen          ###   ########.fr       */
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
	ft_memcpy((void *)data, (void*)&col, (size_t)bytes_pp);
}

static void	point_clip(t_p2d *p, float w, float h, float m, float im)
{
	t_p2d	clamped;

	if (p->x >= 0 && p->x < w && p->y >= 0 && p->y < h)
		return ;
	clamped.x = CLAMP(p->x, 0, w - 1.0f);
	clamped.y = CLAMP(p->y, 0, h - 1.0f);
	if (isfinite(m))
	{
		if (p->x < 0)
			clamped.y = m * (0 - p->x) + p->y;
		else if (p->x > w)
			clamped.y = m * (w - 1.0f - p->x) + p->y;
	}
	*p = clamped;
	if (isfinite(im))
	{
		if (p->y < 0)
			clamped.x = im * (0 - p->y) + p->x;
		else if (p->y > h)
			clamped.x = im * (h - 1.0f - p->y) + p->x;
	}
	*p = clamped;
}

static void	line_clip(t_p2d *a, t_p2d *b, float w, float h)
{
	const float m = (b->y - a->y) / (b->x - a->x);
	const float im = (b->x - a->x) / (b->y - a->y);

	point_clip(a, w, h, m, im);
	point_clip(b, w, h, m, im);
}

void	img_put_line(t_img *img, t_p2d a, t_p2d b, unsigned int col)
{
	long i;
	long steps;
	t_p2d p;

	line_clip(&a, &b, (float)img->w, (float)img->h);
	steps = (long)MAX(ABS(b.x - a.x), ABS(b.y - a.y)) + 1;
	i = 1;
	while (i <= steps)
	{
		p = (t_p2d){ft_lmapf(i, 1, steps, a.x, b.x),
					ft_lmapf(i, 1, steps, a.y, b.y)};
		img_put_pixel(img, (int)p.x, (int)p.y, col);
		i++;
	}
}

void	img_clear(t_img *img)
{
	ft_bzero((void *)img->data, (size_t)(img->stride * img->h));
}
