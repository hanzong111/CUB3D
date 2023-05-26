/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:40:24 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/26 14:22:49 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_wall_info(t_data *data, int x)
{
	double	alpha;
	
	printf("\n\n");
	printf("wall_info[%d]\n", x);
	printf("unit coordinate : <%d,%d>\n", data->temp.final.x, data->temp.final.y);
	// printf("grid coordinate : <%d,%d>\n", data->temp.final.x / 64, data->temp.final.y / 64);
	if (data->temp.final.hit == HORIZONTAL)
	{
		printf("%sWall hit is HORIZONTAL%s\n", RED, DEF);
		if (data->player.facing.y == NORTH)
			printf("Player : NORTH (y)\n");
		else
			printf("Player : SOUTH (y)\n");
	}
	else
	{
		printf("%sWall hit is VERTICAL%s\n", GREEN, DEF);
		if (data->player.facing.x == EAST)
			printf("Player : EAST (x)\n");
		else
			printf("Player : WEST (x)\n");
	}
	// if (data->wall_info[x].wall_dir == NORTH)
	// 	printf("Wall : NORTH (y)\n");
	// else if (data->wall_info[x].wall_dir == SOUTH)
	// 	printf("Wall : SOUTH (y)\n");
	// else if (data->wall_info[x].wall_dir == EAST)
	// 	printf("Wall : EAST (x)\n");
	// else if (data->wall_info[x].wall_dir == WEST)
	// 	printf("Wall : WEST (x)\n");
	alpha = angle_between_vectors(data->player.dir, data->temp.ray_dir);
	printf("Alpha : %f degrees\n", alpha * 180 / M_PI);
	// printf("Ray dir is <%f,%f>\n", data->temp.ray_dir.x, data->temp.ray_dir.y);
	// printf("Projected height is %f\n", data->wall_info[x].projected_h);
	// printf("Sprite col is %d\n", data->wall_info[x].sprite_col);

}