/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:57:59 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/06 16:35:53 by ojing-ha         ###   ########.fr       */
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
}
