/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:57:59 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/12 17:48:58 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	data->player.pos.y = 7 * WALL_H + (WALL_H / 2);
	data->player.dir.x = 0;
	data->player.dir.y = 1;

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
}
