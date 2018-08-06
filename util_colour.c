/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_colour.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:42:16 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/06 14:24:21 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_uint			cmap_get(t_draw *draw, int height)
{
	int				index;
	const t_uint	*colmap = (t_uint *)draw->colmap.data;

	index = height + draw->colmap_offset;
	index = CLAMP(index, 0, (int)draw->colmap.length - 1);
	return (colmap[index]);
}

static t_uint	lerp_byte(float frac, t_uint a, t_uint b, t_byte n)
{
	const float start = (float)((a >> (n * 8)) & 0xFF);
	const float end = (float)((b >> (n * 8)) & 0xFF);

	return ((t_uint)(start + (end - start) * frac));
}

t_uint			colour_lerp(float n, t_uint a, t_uint b)
{
	return (lerp_byte(n, a, b, 0) | (lerp_byte(n, a, b, 1) << 8)
		| (lerp_byte(n, a, b, 2) << 16));
}
