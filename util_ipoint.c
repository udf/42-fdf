/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ipoint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 13:29:20 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/27 13:55:17 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_ip2d			ip2d_add(t_ip2d a, t_ip2d b)
{
	return (t_ip2d){a.x + b.x,  a.y + b.y};
}

t_ip2d			ip2d_sub(t_ip2d a, t_ip2d b)
{
	return (t_ip2d){a.x - b.x,  a.y - b.y};
}

int				ip2d_eq(t_ip2d a, t_ip2d b)
{
	return (a.x == b.x && a.y == b.y);
}

int				ip2d_in_rect(t_ip2d p, size_t w, size_t h)
{
	return (p.x >= 0 && p.x < (ssize_t)w && p.y >= 0 && p.y < (ssize_t)h);
}

size_t			ip2d_to_i(t_ip2d p, size_t w)
{
	return ((size_t)p.x + (size_t)p.y * w);
}
