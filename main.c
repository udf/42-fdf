/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 13:48:12 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/25 08:30:28 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// TODO
// what do return codes from events mean (seem to do nothing)
// wtf is loop hook (runs every tick? (but not on linux because fuck you))

int main(void)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.mlx.ptr = mlx_init();
	if (data.mlx.ptr == NULL)
		return (1);
	data.mlx.win = mlx_new_window(data.mlx.ptr, 900, 900, "fdf");
	if (data.mlx.win == NULL)
		return (1);
	mlx_key_hook(data.mlx.win, key_hook, &data);
	mlx_mouse_hook(data.mlx.win, mouse_hook, &data);
	mlx_expose_hook(data.mlx.win, expose_hook, &data);
	mlx_loop_hook(data.mlx.win, loop_hook, &data);
	mlx_loop(data.mlx.ptr);
	return (0);
}
