/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:53:55 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/09 23:45:14 by ojing-ha         ###   ########.fr       */
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

void	get_player_dir(t_temp *temp, t_player *player)
{
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

void	fill_in_wall_info(t_data *data, int x)
{
	double	d;
	double	alpha;

	d = calculate_distance(data->player.pos, data->temp.final);
	alpha = angle_between_vectors(data->player.dir, data->temp.ray_dir);
	// printf("distance is %f\n", d);
	d = ceil(d * cos(alpha));
	// printf("distance after correction is %f\n", d);
	data->wall_info[x].projected_h = ceil((data->info.d_to_plane * WALL_H) / d);
	get_player_dir(&data->temp, &data->player);
	data->wall_info[x].wall_dir = get_wall_dir(&data->temp, &data->player);
	if (data->temp.final.hit == HORIZONTAL)
	{
		while (data->temp.final.x >= 64)
			data->temp.final.x -= 64;
		data->wall_info[x].sprite_col = data->temp.final.x;
	}
	else if (data->temp.final.hit == VERTICAL)
	{
		while (data->temp.final.y >= 64)
			data->temp.final.y -= 64;
		data->wall_info[x].sprite_col = 64 - data->temp.final.y;
	}
}

void	print_wall_info(t_data *data, int x)
{
	double	alpha;
	
	printf("\n\n");
	printf("wall_info[%d]\n", x);
	// printf("unit coordinate : <%d,%d>\n", data->temp.final.x, data->temp.final.y);
	printf("grid coordinate : <%d,%d>\n", data->temp.final.x / 64, data->temp.final.y / 64);
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
	printf("Sprite col is %d\n", data->wall_info[x].sprite_col);

}

void	raytracer(t_data *data, char grid[9][9])
{
	int	x;

	x = 0;
	data->temp.ray_dir = rotate_vector((data->info.player_fov / 2)
			* M_PI / 180, data->player.dir);
	// data->temp.ray_dir = rotate_vector((45)
	// 		* M_PI / 180, data->player.dir);
	data->temp.final = ray_find_wall(data, grid);
	fill_in_wall_info(data, x);
	print_wall_info(data, x);
	while (++x < SCREEN_W)
	{
		data->temp.ray_dir = rotate_vector(-data->info.angle_between_rays,
				data->temp.ray_dir);
		data->temp.final = ray_find_wall(data, grid);
		fill_in_wall_info(data, x);
		print_wall_info(data, x);
	}
}
