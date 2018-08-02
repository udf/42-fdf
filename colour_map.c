/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:16:36 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/02 17:00:12 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_hex_digit(char c, t_byte *out)
{
	c = (char)ft_tolower((char)c);
	if (ft_isdigit(c))
		*out = (t_byte)c - '0';
	else if (c >= 'a' && c <= 'f')
		*out = (t_byte)c - 'a' + 10;
	else
		return (1);
	return (0);
}

static char	*parse_colour(char *str, int *out_h, t_uint *colour)
{
	size_t	i;
	t_byte	hex_digit;

	*out_h = ft_atoi(str);
	while (*str && *str != ':')
		str++;
	if (!*str)
		return ("Colour map: failed to find RGB hex");
	str++;
	*colour = 0;
	i = 0;
	while (*str && i < 6)
	{
		if (parse_hex_digit(*str, &hex_digit))
			return ("Colour map: Invalid character in RGB hex");
		*colour = *colour * 16 + hex_digit;
		i++;
		str++;
	}
	if (i != 6)
		return ("Colour map: not enough characters in RGB hex");
	if (*str)
		return ("Colour map: foreign characters after RGB hex");
	return (NULL);
}

static char	*measure_cmap_size(t_data *data, int ac, char **av)
{
	char	*err;
	int		height;
	size_t	max_height;
	t_uint	colour;
	t_vec	*colmap;

	max_height = 0;
	colmap = &data->draw.colmap;
	while (ac > 0)
	{
		if ((err = parse_colour(av[ac - 1], &height, &colour)))
			return (err);
		if (height > (int)max_height)
			max_height = (size_t)height;
		if (-height > (int)data->draw.colmap_offset)
			data->draw.colmap_offset = (size_t)(-height);
		vec_reserve(colmap,
			(size_t)(data->draw.colmap_offset + max_height + 1));
		ac--;
	}
	colmap->length = colmap->mem_size / colmap->type_size;
	printf("measure: cmap vec is now at %zu elems\n", colmap->length);
	return (NULL);
}

static void	interpolate_colour_map(t_uint *colmap, size_t length)
{
	size_t i;
	size_t start;
	size_t end;

	i = 1;
	start = 0;
	end = 1;
	while (end < length && colmap[end] > 0xFFFFFF)
		end++;
	while (i < length)
	{
		if (end >= length)
			break;
		if (colmap[i] > 0xFFFFFF)
			colmap[i] = colour_lerp((float)(i - start) / (float)(end - start),
				colmap[start], colmap[end]);
		else
		{
			start = i;
			end = start + 1;
			while (end < length && colmap[end] > 0xFFFFFF)
				end++;
		}
		i++;
	}

	i = 0;
	while (i < length)
	{
		printf("%zu: %08x\n", i, colmap[i]);
		i++;
	}
}

char		*load_colour_map(t_data *data, int ac, char **av)
{
	char	*err;
	int		height;
	t_uint	colour;
	t_uint	*colmap;

	if ((err = measure_cmap_size(data, ac, av)))
		return (err);
	colour = 0xFFFFFFF;
	vec_fill(&data->draw.colmap, &colour);
	colour = 0xFFFFF;
	if (data->draw.colmap.length == 0)
		vec_append(&data->draw.colmap, &colour);
	colmap = (t_uint *)data->draw.colmap.data;
	while (ac > 0)
	{
		if ((err = parse_colour(av[ac - 1], &height, &colour)))
			return (err);
		colmap[height + (int)data->draw.colmap_offset] = colour;
		ac--;
	}
	interpolate_colour_map(colmap, data->draw.colmap.length);
	return (NULL);
}
