/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_wall_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:45:52 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/18 21:09:24 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_player_dir(t_temp *temp, t_player *player)
{
	player->facing.x = 0;
	player->facing.y = 0;
	if (temp->ray_dir.x > 0)
		player->facing.x = EAST;
	else
		player->facing.x = WEST;
	if (temp->ray_dir.y > 0)
		player->facing.y = NORTH;
	else
		player->facing.y = SOUTH;
}

int	get_wall_dir(t_temp *temp, t_player *player)
{
	if (temp->final.hit == HORIZONTAL)
	{
		if (player->facing.y == NORTH)
			return (SOUTH);
		else
			return (NORTH);
	}
	else if (temp->final.hit == VERTICAL)
	{
		if (player->facing.x == EAST)
			return (WEST);
		else
			return (EAST);
	}
	return (0);
}

int	get_sprite_col(t_temp	*temp)
{
	int	col;

	if (temp->final.hit == HORIZONTAL)
		col = temp->final.x;
	else
		col = temp->final.y;
	while (col >= WALL_H)
		col -= WALL_H;
	return (col);
}

void	fill_in_wall_info(t_data *data, int x)
{
	double	d;
	double	alpha;

	d = calculate_distance(data->player.pos, data->temp.final);
	alpha = angle_between_vectors(data->player.dir, data->temp.ray_dir);
	if (!isnan(alpha))
		d = d * cos(alpha);
	data->wall_info[x].projected_h = ceil((data->info.d_to_plane * WALL_H) / d);
	get_player_dir(&data->temp, &data->player);
	data->wall_info[x].wall_dir = get_wall_dir(&data->temp, &data->player);
	data->wall_info[x].sprite_col = get_sprite_col(&data->temp);
}
