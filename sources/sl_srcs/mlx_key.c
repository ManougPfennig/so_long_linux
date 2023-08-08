/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:56:15 by mapfenni          #+#    #+#             */
/*   Updated: 2023/06/07 18:12:16 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_pressed(int key, t_data *data)
{
	if (data->victory)
		sprite_to_win(data, 'X', 0, 0);
	else if (key == W_KEY)
		move_player(data, 0, -1);
	else if (key == A_KEY)
		move_player(data, -1, 0);
	else if (key == S_KEY)
		move_player(data, 0, 1);
	else if (key == D_KEY)
		move_player(data, 1, 0);
	if (key == ESC_KEY)
	{
		mlx_destroy_window(data->mlx, data->win);
		ft_free_tab(data->map, data->copy_map);
		print_error("Exiting...\n");
	}
	return (0);
}

int	key_release(int key, t_data *data)
{
	(void)key;
	(void)data;
	return (0);
}

int	deal_key(t_data *data)
{
	(void)data;
	return (0);
}
