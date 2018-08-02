/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 14:35:09 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 13:39:35 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char		*read_vert_row(t_draw *draw, size_t y, char **split)
{
	size_t	w;
	t_p3d	p;

	w = 0;
	p.y = (float)y;
	while (*split)
	{
		p.z = (float)ft_atoi(*split);
		p.x = (float)w;
		vec_append(&draw->verts, &p);
		w++;
		split++;
	}
	if (!draw->map_w)
		draw->map_w = w;
	if (w != draw->map_w || w == 0)
		return ("Invalid number of heights in map");
	return (NULL);
}

static void		make_lines(t_draw *draw, t_ip2d start, t_ip2d dir)
{
	const size_t	w = draw->map_w;
	const size_t	h = draw->map_h;
	t_ip2d			end;
	t_ipair			l;

	while (ip2d_in_rect(ip2d_add(start, dir), w, h))
	{
		end = ip2d_add(start, dir);
		if (!ip2d_in_rect(end, w, h))
			return ;
		l = (t_ipair){ip2d_to_i(start, w), ip2d_to_i(end, w)};
		vec_append(&draw->lines, &l);
		start = end;
	}
}

static void		make_grid_lines(t_draw *draw)
{
	t_ip2d	start;

	start.x = 0;
	start.y = 0;
	while (start.y < (ssize_t)draw->map_h)
	{
		make_lines(draw, start, (t_ip2d){1, 0});
		start.y++;
	}
	start.y = 0;
	while (start.x < (ssize_t)draw->map_w)
	{
		make_lines(draw, start, (t_ip2d){0, 1});
		start.x++;
	}
}

char			*load_map(t_draw *draw, char *path)
{
	int		fd;
	char	*line;
	char	**split;

	if ((fd = open(path, O_RDONLY)) < 0)
		return ("Failed to open map file");
	draw->map_h = 0;
	while (get_next_line(fd, &line) == GNL_SUCCESS)
	{
		split = ft_strsplit(line, ' ');
		free(line);
		if (!split)
			return ("Failed to read map line");
		line = read_vert_row(draw, draw->map_h, split);
		ft_tabfree((void **)split);
		if (line)
			return (line);
		draw->map_h++;
	}
	close(fd);
	if (draw->map_h == 0)
		return ("Error: Map is empty");
	make_grid_lines(draw);
	return (NULL);
}
