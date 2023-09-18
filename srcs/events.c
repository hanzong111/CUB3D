/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:50:00 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/18 21:08:59 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	event(int keycode, t_data *data)
{
	if (keycode == ESC_KEY)
	{
		ft_printf("Esc pressed.\n");
		ft_printf("Exiting so_long ...\n");
		exit(0);
	}
	if (keycode == W_KEY || keycode == S_KEY
		|| keycode == A_KEY || keycode == D_KEY)
		move_player(data, keycode);
	if (keycode == LEFT_ARROW)
		data->player.dir = rotate_vector((TURN_SPEED)
				* M_PI / 180, data->player.dir);
	if (keycode == RIGHT_ARROW)
		data->player.dir = rotate_vector(-(TURN_SPEED)
				* M_PI / 180, data->player.dir);
	return (0);
}

int	sl_close_window(t_data *data)
{
	(void)data;
	ft_printf("Window closed.\n");
	ft_printf("Exiting cub3d...\n");
	exit(0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	data->temp.keycode = keycode;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	(void)keycode;
	data->temp.keycode = -1;
	return (0);
}
