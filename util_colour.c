/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_colour.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 16:42:16 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 17:03:17 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_uint	cmap_get(t_draw *draw, int height)
{
	int index;

	index = height + (int)draw->colmap_offset;
	index = CLAMP(index, 0, (int)draw->colmap.length);
	return (((t_uint *)draw->colmap.data)[index]);
}

t_byte	get_byte(t_uint a, t_byte n)
{
	return ((a >> (n * 8)) & 0xFF);
}

t_uint	lerp_byte(float frac, t_uint a, t_uint b, t_byte n)
{
	return ((t_uint)ft_lmapl(frac, 0, 1, get_byte(a, n), get_byte(b, n)));
}

t_uint	colour_lerp(float n, t_uint a, t_uint b)
{
	return (lerp_byte(n, a, b, 0) | (lerp_byte(n, a, b, 1) << 8)
		| (lerp_byte(n, a, b, 2) << 16));
}