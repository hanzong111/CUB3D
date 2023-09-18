/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:12:00 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/18 21:12:43 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_collision(char **grid, double x, double y)
{
	if (grid[(int)y / 64][(int)x / 64] == '1')
		return (0);
	return (1);
}

void	move_player(t_data *data, int keycode)
{
	t_dvct	move_dir;

	move_dir.x = 0;
	move_dir.y = 0;
	if (keycode == W_KEY)
		move_dir = rotate_vector(0, data->player.dir);
	else if (keycode == A_KEY)
		move_dir = rotate_vector(90 * M_PI / 180, data->player.dir);
	else if (keycode == D_KEY)
		move_dir = rotate_vector(-90 * M_PI / 180, data->player.dir);
	else if (keycode == S_KEY)
		move_dir = rotate_vector(180 * M_PI / 180, data->player.dir);
	move_dir.x *= MOVE_SPEED;
	move_dir.y *= MOVE_SPEED;
	move_dir.y *= -1;
	if (check_collision(data->game.map, (data->player.pos.x + (int)move_dir.x),
			(data->player.pos.y + (int)move_dir.y)))
	{
		data->player.pos.x = (data->player.pos.x + (int)move_dir.x);
		data->player.pos.y = (data->player.pos.y + (int)move_dir.y);
	}
}
