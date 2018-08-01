/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 18:52:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/08/01 14:41:30 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	process_btn_changes(t_data *data)
{
	size_t i;
	t_input *input;

	i = 0;
	input = &data->input;
	while (i < MOUSE_MAX)
	{
		input->m.btn[i].changed = input->m.btn[i].down ^ input->m.btn[i].last;
		input->m.btn[i].last = input->m.btn[i].down;
		i++;
	}
}

int	loop(t_data *data)
{
	process_btn_changes(data);
	draw(data);
	return (0);
}
