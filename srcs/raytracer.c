/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:53:55 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/26 17:18:44 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*	Find Intersections and decides which point/wall 	*/
/*	does the player sees first							*/
t_ivct	ray_find_wall(t_data *data, char **grid, t_temp temp)
{
	double	horizontal;
	double	vertical;

	find_horizontal(data, grid);
	find_vertical(data, grid);
	if (data->temp.v1.x == OUT_OF_BOUND && data->temp.v2.y == OUT_OF_BOUND)
		return (data->temp.v2);
	else if (data->temp.v2.x == OUT_OF_BOUND && data->temp.v2.y == OUT_OF_BOUND)
		return (data->temp.v1);
	horizontal = calculate_distance(data->player.pos, data->temp.v1);
	vertical = calculate_distance(data->player.pos, data->temp.v2);
	if (fabs(horizontal - vertical) < __FLT_EPSILON__)
	{
		if (temp.ray_dir.x > 0 && temp.ray_dir.y > 0)
			return (data->temp.v2);
		else
			return (data->temp.v1);
	}
	if (horizontal < vertical)
		return (data->temp.v1);
	else
		return (data->temp.v2);
}

void	raytracer(t_data *data, char **grid)
{
	int	x;

	x = -1;
	data->temp.ray_dir = rotate_vector((data->info.player_fov / 2)
			* M_PI / 180, data->player.dir);
	while (++x < SCREEN_W)
	{
		data->temp.ray_dir = rotate_vector(-data->info.angle_between_rays,
				data->temp.ray_dir);
		data->temp.final = ray_find_wall(data, grid, data->temp);
		fill_in_wall_info(data, x);
		// print_wall_info(data, x);
	}
}
