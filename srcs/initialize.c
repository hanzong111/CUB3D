/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:57:59 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/18 21:09:42 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_size(t_collide *col, char **grid)
{
	int	i;

	col->grid_size.y = 0;
	while (grid[col->grid_size.y] != NULL)
		col->grid_size.y++;
	col->row_length = malloc(sizeof(int) * col->grid_size.y);
	i = -1;
	while (++i < col->grid_size.y)
		col->row_length[i] = ft_strlen(grid[i]);
}

void	initialize(t_data *data)
{
	data->render.sky.r = -1;
	data->render.sky.g = -1;
	data->render.sky.b = -1;
	data->render.floor.r = -1;
	data->render.floor.g = -1;
	data->render.floor.b = -1;
	data->sprites.n_img.img = NULL;
	data->sprites.s_img.img = NULL;
	data->sprites.e_img.img = NULL;
	data->sprites.w_img.img = NULL;
	data->count.n_img = 0;
	data->count.s_img = 0;
	data->count.e_img = 0;
	data->count.w_img = 0;
	data->count.sky = 0;
	data->count.floor = 0;
	data->info.player_height = 32;
	data->info.player_fov = 60;
	data->info.d_to_plane = (SCREEN_W / 2)
		/ tan((data->info.player_fov / 2) * M_PI / 180);
	data->info.angle_between_rays = (data->info.player_fov
			/ SCREEN_W) * M_PI / 180;
	data->wall_info = malloc(sizeof(t_wallinfo) * SCREEN_W);
}
