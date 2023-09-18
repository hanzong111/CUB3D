/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:05:34 by gualee            #+#    #+#             */
/*   Updated: 2023/09/18 21:05:34 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_wall_details(t_data *data, int x)
{
	double	alpha;

	printf("wall_info[%d]\n", x);
	printf("unit coordinate : <%d,%d>\n",
		data->temp.final.x, data->temp.final.y);
	printf("grid coordinate : <%d,%d>\n",
		data->temp.final.x / 64, data->temp.final.y / 64);
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
	alpha = angle_between_vectors(data->player.dir, data->temp.ray_dir);
	printf("Alpha : %f degrees\n", alpha * 180 / M_PI);
}
