/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojing-ha <ojing-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:53:55 by ojing-ha          #+#    #+#             */
/*   Updated: 2023/05/13 22:44:49 by ojing-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*	export DISPLAY=localhost:0.0	*/
/*	65307 || 53						*/
/* 	W  	  || 13						*/
/*	S  	  || 1						*/
/* 	A  	  || 0						*/
/*	D  	  || 2						*/

// int	event(int keycode, t_data *data)
// {
// 	if (keycode == 65307)
// 	{
// 		ft_printf("Esc pressed.\n");
// 		ft_printf("Exiting so_long ...\n");
// 		exit(0);
// 	}
// 	if (keycode == 'w')
// 		sl_lstadd_back(&data->player.move_list, sl_lstnew(MOVE_UP));
// 	if (keycode == 's')
// 		sl_lstadd_back(&data->player.move_list, sl_lstnew(MOVE_DOWN));
// 	if (keycode == 'a')
// 		sl_lstadd_back(&data->player.move_list, sl_lstnew(MOVE_LEFT));
// 	if (keycode == 'd')
// 		sl_lstadd_back(&data->player.move_list, sl_lstnew(MOVE_RIGHT));
// 	return (0);
// }

// int	render_next_frame(t_data *data)
// {
// 	static int	tick;

// 	tick++;
// 	check_move_list(data);
// 	choose_frame(tick, data);
// 	render_map(data);
// 	if (data->map.enemy != 0)
// 		add_enemy(data);
// 	generate_ui(data);
// 	mlx_put_image_to_window(data->mlx, data->window, data->final_img.img, 0, 0);
// 	mlx_destroy_image(data->mlx, data->final_img.img);
// 	return (0);
// }

int	sl_close_window(t_data *data)
{
	data->start_x = 3;
	ft_printf("Window closed.\n");
	ft_printf("Exiting cub3d...\n");
	exit(0);
	return (0);
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

int	get_start_pixel(int	projected_h)
{
	if (projected_h >= SCREEN_H)
		return (0);
	return((SCREEN_H / 2) - (projected_h / 2));
}

void	draw_walls(t_rgb color, t_data_addr d, int	height, int width)
{
	while (height < SCREEN_H)
	{
		d.address[height * d.size_line + width * d.pixel_bits / 8] = color.b;
		d.address[height * d.size_line + width * d.pixel_bits / 8 + 1] = color.g;
		d.address[height * d.size_line + width * d.pixel_bits / 8 + 2] = color.r;
		height++;
	}
}

void	draw_sky_floor(t_render *render, t_data_addr d)
{
	t_rgb	color;
	int		x;
	int		y;

	y = -1;
	while (++y < SCREEN_H)
	{
		if (y < (SCREEN_H / 2))
			color = render->sky;
		else
			color = render->floor;
		x = -1;
		while (++x < SCREEN_W)
		{
			d.address[y * d.size_line + x * d.pixel_bits / 8] = color.b;
			d.address[y * d.size_line + x * d.pixel_bits / 8 + 1] = color.g;
			d.address[y * d.size_line + x * d.pixel_bits / 8 + 2] = color.r;
		}
	}

}

void	render(t_data *data)
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
		start_pixel = get_start_pixel(data->wall_info[x].projected_h);
		while (start_pixel < SCREEN_H && data->wall_info[x].projected_h >= 0)
		{
		des.address[start_pixel * des.size_line + x * des.pixel_bits / 8] = color.b;
		des.address[start_pixel * des.size_line + x * des.pixel_bits / 8 + 1] = color.g;
		des.address[start_pixel * des.size_line + x * des.pixel_bits / 8 + 2] = color.r;
		start_pixel++;
		data->wall_info[x].projected_h--;
		}
	}

}

int	main(int argc, char **argv)
{
	t_data			data;
	char			grid[9][9] = 
	{	{'1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '1', '1', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', 'P', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1'}};
	initialize(&data);
	raytracer(&data, grid);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, SCREEN_W, SCREEN_H, "so_long");
	data.final_img.img = mlx_new_image(data.mlx, SCREEN_W, SCREEN_H);
	data.final_img.w = SCREEN_W;
	data.final_img.h = SCREEN_H;
	render(&data);
	mlx_put_image_to_window(data.mlx, data.window, data.final_img.img, 0, 0);
	(void)argc;
	(void)argv;
	// mlx_loop_hook(data.mlx, render_next_frame, &data);
	// mlx_key_hook(data.window, event, &data);
	// mlx_hook(data.window, ON_DESTROY, 0L, sl_close_window, &data);
	free(data.wall_info);
	mlx_loop(data.mlx);
}
