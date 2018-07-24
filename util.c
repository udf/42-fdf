/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhoosen <mhoosen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 15:25:13 by mhoosen           #+#    #+#             */
/*   Updated: 2018/07/24 15:27:21 by mhoosen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void die(t_data data, char *msg)
{
	if (msg && *msg)
		ft_putendl_fd(msg, 2);
	if (data.mlx.win)
	{
		printf("Destroying window...\n");
		mlx_destroy_window(data.mlx.ptr, data.mlx.win);
	}
	printf("exiting...\n");
	exit(0);
}
