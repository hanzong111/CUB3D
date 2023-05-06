/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:53:55 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/07 00:05:11 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*	Find Intersections and decides which point/wall 	*/
/*	does the player sees first							*/
t_ivct	ray_find_wall(t_data *data, char grid[9][9])
{
	double	d1;
	double	d2;

	find_horizontal(&data->player, &data->temp, &data->col, grid);
	find_vertical(&data->player, &data->temp, &data->col, grid);
	if (data->temp.v1.x == OUT_OF_BOUND && data->temp.v2.y == OUT_OF_BOUND)
		return (data->temp.v2);
	else if (data->temp.v2.x == OUT_OF_BOUND && data->temp.v2.y == OUT_OF_BOUND)
		return (data->temp.v1);
	d1 = calculate_distance(data->player.pos, data->temp.v1);
	d2 = calculate_distance(data->player.pos, data->temp.v2);
	if (d1 <= d2)
		return (data->temp.v1);
	else
		return (data->temp.v2);
}

// t_wallinfo	fill_in_wall_info(t_data *data)
// {
// 	t_wallinfo	wall;
// }

t_dvct	rotate_vector(double rad, t_dvct v)
{
	t_dvct	temp;

	temp.x = cos(rad) * v.x - sin(rad) * v.y;
	temp.y = sin(rad) * v.x + cos(rad) * v.y;
	return (temp);
}

void	raytracer(t_data *data, char grid[9][9])
{
	int	x;

	x = -1;
	data->temp.ray_dir = rotate_vector((data->info.player_fov / 2)
			* M_PI / 180, data->player.dir);
	while (++x < SCREEN_W)
	{
		data->temp.final = ray_find_wall(data, grid);
		// data->wall_info[x] = fill_in_wall_info(data);
	}
}
