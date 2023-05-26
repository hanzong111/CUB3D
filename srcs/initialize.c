/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:57:59 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/26 17:12:18 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_size(t_collide *col, char **grid)
{
	col->grid_size.x = ft_strlen(grid[0]);
	col->grid_size.y = 0;
	while (grid[col->grid_size.y] != NULL)
		col->grid_size.y++;
}

void	initialize(t_data *data)
{
	data->info.player_height = 32;
	data->info.player_fov = 60;
	data->info.d_to_plane = (SCREEN_W / 2)
		/ tan((data->info.player_fov / 2) * M_PI / 180);
	data->info.angle_between_rays = (data->info.player_fov
			/ SCREEN_W) * M_PI / 180;
	data->wall_info = malloc(sizeof(t_wallinfo) * SCREEN_W);
	/*	Will be input in the future	*/
	data->player.pos.x = 4 * WALL_H + (WALL_H / 2);
	data->player.pos.y = 6 * WALL_H + (WALL_H / 2);
	data->player.dir.x = 0;
	data->player.dir.y = -1;

	/*	Red	*/
	data->render.north.r = 255;
	data->render.north.g = 153;
	data->render.north.b = 153;

	/*	Orange	*/
	data->render.south.r = 255;
	data->render.south.g = 204;
	data->render.south.b = 153;

	/*	Blue-Purple	*/
	data->render.east.r = 153;
	data->render.east.g = 153;
	data->render.east.b = 255;
	
	/*	Indigo	*/
	data->render.west.r = 204;
	data->render.west.g = 153;
	data->render.west.b = 255;

	data->render.sky.r = 153;
	data->render.sky.g = 255;
	data->render.sky.b = 255;

	data->render.floor.r = 255;
	data->render.floor.g = 255;
	data->render.floor.b = 153;
	map_size(&data->col, data->grid);
}
