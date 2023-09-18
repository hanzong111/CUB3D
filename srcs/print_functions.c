/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gualee <gualee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:40:24 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/09/18 21:06:13 by gualee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_wall_info(t_data *data, int x)
{
	printf("\n\n");
	print_wall_details(data, x);
	if (data->wall_info[x].wall_dir == NORTH)
		printf("Wall : NORTH (y)\n");
	else if (data->wall_info[x].wall_dir == SOUTH)
		printf("Wall : SOUTH (y)\n");
	else if (data->wall_info[x].wall_dir == EAST)
		printf("Wall : EAST (x)\n");
	else if (data->wall_info[x].wall_dir == WEST)
		printf("Wall : WEST (x)\n");
	printf("Ray dir is <%f,%f>\n", data->temp.ray_dir.x, data->temp.ray_dir.y);
	printf("Projected height is %f\n", data->wall_info[x].projected_h);
	printf("Sprite col is %d\n", data->wall_info[x].sprite_col);
}

t_rgb	get_color(t_wallinfo wall, t_render r)
{
	if (wall.wall_dir == NORTH)
		return (r.north);
	else if (wall.wall_dir == SOUTH)
		return (r.south);
	else if (wall.wall_dir == EAST)
		return (r.east);
	else
		return (r.west);
}

int	get_start_pixel_color(int projected_h)
{
	if (projected_h >= SCREEN_H)
		return (0);
	return ((SCREEN_H / 2) - (projected_h / 2));
}

void	draw_walls(t_rgb color, t_data_addr d, int height, int width)
{
	while (height < SCREEN_H)
	{
		d.address[height * d.size_line
			+ width * d.pixel_bits / 8] = color.b;
		d.address[height * d.size_line
			+ width * d.pixel_bits / 8 + 1] = color.g;
		d.address[height * d.size_line
			+ width * d.pixel_bits / 8 + 2] = color.r;
		height++;
	}
}

void	render_simple_color(t_data *data)
{
	int			x;
	int			start_pixel;
	t_rgb		color;
	t_data_addr	des;

	x = -1;
	des.address = mlx_get_data_addr(data->final_img.img, &des.pixel_bits,
			&des.size_line, &des.endian);
	draw_sky_floor(&data->render, des);
	while (++x < SCREEN_W)
	{
		color = get_color(data->wall_info[x], data->render);
		start_pixel = get_start_pixel_color(data->wall_info[x].projected_h);
		while (start_pixel < SCREEN_H && data->wall_info[x].projected_h >= 0)
		{
			des.address[start_pixel * des.size_line
				+ x * des.pixel_bits / 8] = color.b;
			des.address[start_pixel * des.size_line
				+ x * des.pixel_bits / 8 + 1] = color.g;
			des.address[start_pixel * des.size_line
				+ x * des.pixel_bits / 8 + 2] = color.r;
			start_pixel++;
			data->wall_info[x].projected_h--;
		}
	}
}
