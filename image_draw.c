/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 21:59:08 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 13:54:15 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	point_clip(t_p2d *p, float w, float h, t_p2d m)
{
	t_p2d	clamped;

	clamped.x = CLAMP(p->x, 0, w - 1.0f);
	if (isfinite(m.y))
		p->y = m.y * (clamped.x - p->x) + p->y;
	p->x = clamped.x;
	clamped.y = CLAMP(p->y, 0, h - 1.0f);
	if (isfinite(m.x))
		p->x = m.x * (clamped.y - p->y) + p->x;
	p->y = clamped.y;
}

static int	line_clip(t_p2d *a, t_p2d *b, float w, float h)
{
	const t_p2d m = {(b->x - a->x) / (b->y - a->y),

	(b->y - a->y) / (b->x - a->x)};
	point_clip(a, w, h, m);
	point_clip(b, w, h, m);
	return ((a->x < 0 || a->x >= w || a->y < 0 || a->y >= h)
				&& (b->x < 0 || b->x >= w || b->y < 0 || b->y >= h));
}

void		img_put_pixel(t_img *img, int x, int y, t_uint col)
{
	const int	bytes_pp = img->stride / img->w;
	char		*data;

	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	data = img->data + x * bytes_pp + y * img->stride;
	*((t_uint *)data) = col;
}

void		img_put_line(t_img *img, t_p2d a, t_p2d b, t_uint col)
{
	long	i;
	long	steps;
	t_p2d	p;

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

void		img_clear(t_img *img)
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
